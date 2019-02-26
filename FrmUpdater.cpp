#include "FrmUpdater.h"
#include "Global/GlobalDir.h"
#include "ui_FrmUpdater.h"
#include <QtNetwork>
#include <QUrl>
#include <QDebug>
#include <QStandardPaths>
#include <QFinalState>
#include <QDomDocument>
#include <QDomText>
#include <QDomElement>
#include <QProcess>
#include <QDir>
#include <QSsl>

CFrmUpdater::CFrmUpdater(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmUpdater),
    m_ButtonGroup(this),
    m_NetManager(this),
    m_pReply(nullptr)
{
    bool check = false;
    m_bDownload = false;
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);
    ui->lbNewArch->hide();
    ui->lbNewVersion->hide();
    ui->progressBar->hide();
    ui->pbOK->hide();
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(), QSettings::IniFormat);
    int id = set.value("Update/RadioButton", -2).toInt();
    m_ButtonGroup.addButton(ui->rbEveryTime);
    m_ButtonGroup.addButton(ui->rbEveryDate);
    m_ButtonGroup.addButton(ui->rbEveryWeek);
    m_ButtonGroup.addButton(ui->rbEveryMonth);
    m_ButtonGroup.button(id)->setChecked(true);
    check = connect(&m_ButtonGroup, SIGNAL(buttonClicked(int)),
                    this, SLOT(slotButtonClickd(int)));
    Q_ASSERT(check);
    SetTitle(qApp->applicationDisplayName());
    
    SetArch(BUILD_ARCH);
    SetVersion(BUILD_VERSION);

    QString szUrl = "https://raw.githubusercontent.com/KangLin/"
            + qApp->applicationName() +"/master/Update/update_";
#if defined (Q_OS_WIN)
    szUrl += "windows";
#elif defined(Q_OS_ANDROID)
    szUrl += "android";
#elif defined (Q_OS_LINUX)
    szUrl += "linux";
#endif
    szUrl += ".xml";
    DownloadFile(QUrl(szUrl));
    
    InitStateMachine();
}

CFrmUpdater::~CFrmUpdater()
{
    delete ui;
}

int CFrmUpdater::InitStateMachine()
{
    QFinalState *sFinal = new QFinalState();
    QState *sCheck = new QState();
    QState *s = new QState();
    QState *sDownloadXmlFile = new QState(s);
    QState *sDownload = new QState(s);
    QState *sUpdate = new QState(s);

    sCheck->addTransition(this, SIGNAL(sigError()), sFinal);
    sCheck->addTransition(this, SIGNAL(sigFinished()), s);
    bool check = connect(sCheck, SIGNAL(entered()), this, SLOT(slotCheck()));

    s->addTransition(this, SIGNAL(sigError()), sFinal);
    s->addTransition(this, SIGNAL(sigFinished()), sFinal);

    s->setInitialState(sDownloadXmlFile);
    sDownloadXmlFile->addTransition(this, SIGNAL(sigDownloadFinished()), sDownload);
    sDownload->addTransition(this, SIGNAL(sigDownloadFinished()), sUpdate);
    sDownloadXmlFile->assignProperty(ui->lbState, "text", tr("Being download xml file"));
    sDownload->assignProperty(ui->lbState, "text", tr("Being download update file"));
    sUpdate->assignProperty(ui->lbState, "text", tr("Being install update"));
    check = connect(sDownloadXmlFile, SIGNAL(entered()),
                     this, SLOT(slotDownloadXmlFile()));
    Q_ASSERT(check);
    check = connect(sDownload, SIGNAL(entered()), this, SLOT(slotDownload()));
    Q_ASSERT(check);
    check = connect(sUpdate, SIGNAL(entered()), this, SLOT(slotUpdate()));
    Q_ASSERT(check);
    
    m_StateMachine.addState(sCheck);    
    m_StateMachine.addState(s);
    m_StateMachine.addState(sFinal);
    m_StateMachine.setInitialState(sCheck);
    m_StateMachine.start();
    return 0;    
}

int CFrmUpdater::SetTitle(const QString &szTitle, QPixmap icon)
{
    ui->lbTitle->setText(szTitle);
    QPixmap pixmpa = icon;
    if(pixmpa.isNull())
        pixmpa.load(":/icon/App", "PNG");
    ui->lbTitleIcon->setPixmap(pixmpa);
    return 0;
}

int CFrmUpdater::SetArch(const QString &szArch)
{
    m_szCurrentArch = szArch;
    ui->lbCurrentArch->setText(tr("Current archecture: %1")
                               .arg(m_szCurrentArch));
    return 0;
}

int CFrmUpdater::SetVersion(const QString &szVersion)
{
    m_szCurrentVersion = szVersion;
    ui->lbCurrentVersion->setText(tr("Current version: %1")
                                  .arg(m_szCurrentVersion));
    return 0;
}

int CFrmUpdater::DownloadFile(const QUrl &url, bool bRedirection, bool bDownload)
{
    int nRet = 0;

    if(!m_StateMachine.isRunning())
    {
        m_bDownload = bDownload;        
        m_Url = url;
        return 0;
    }
    
    if(url.isLocalFile())
    {
        m_DownloadFile.setFileName(url.toLocalFile());
        emit sigDownloadFinished();
        return 0;
    }

    if(!bRedirection)
    {
        QString szTmp
                = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
        szTmp = szTmp + QDir::separator() + "Rabbit"
                + QDir::separator() + qApp->applicationName();
        QDir d;
        if(!d.exists(szTmp))
            d.mkpath(szTmp);
        QString szPath = url.path();   
        QString szFile = szTmp + szPath.mid(szPath.lastIndexOf("/"));
        m_DownloadFile.setFileName(szFile);
        qDebug() << "CFrmUpdater download file: " << m_DownloadFile.fileName();
        if(!m_DownloadFile.open(QIODevice::WriteOnly))
        {
            qDebug() << "Open file fail: " << szFile;
            return -1;
        }
    }

    QNetworkRequest request(url);
    //https://blog.csdn.net/itjobtxq/article/details/8244509
    /*QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::AnyProtocol);
    request.setSslConfiguration(config);
    */
    m_pReply = m_NetManager.get(request);
    if(!m_pReply)
        return -1;
    
    bool check = false;
    check = connect(m_pReply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    Q_ASSERT(check);
    check = connect(m_pReply, SIGNAL(downloadProgress(qint64, qint64)),
                    this, SLOT(slotDownloadProgress(qint64, qint64)));
    Q_ASSERT(check);
    check = connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)),
                    this, SLOT(slotError(QNetworkReply::NetworkError)));
    Q_ASSERT(check);
    check = connect(m_pReply, SIGNAL(sslErrors(const QList<QSslError>)),
                    this, SLOT(slotSslError(const QList<QSslError>)));
    check = connect(m_pReply, SIGNAL(finished()),
                    this, SLOT(slotFinished()));
    
    ui->progressBar->show();
    return nRet;
}

void CFrmUpdater::slotReadyRead()
{
    qDebug() << "CFrmUpdater::slotReadyRead()";
    if(m_DownloadFile.isOpen() && m_pReply)
    {
        QByteArray d = m_pReply->readAll();
        //qDebug() << d;
        m_DownloadFile.write(d);
    }
}

void CFrmUpdater::slotFinished()
{
    qDebug() << "CFrmUpdater::slotFinished()";
    
    QVariant redirectionTarget
            = m_pReply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(!redirectionTarget.isNull())
    {
        m_pReply->disconnect();
        m_pReply->deleteLater();
        m_pReply = nullptr;
        QUrl u = redirectionTarget.toUrl();
        
        if(u.isValid())
        {
            DownloadFile(u, false);
        }
        return;
    }
    
    if(m_pReply)
    {
        m_pReply->disconnect();
        m_pReply->deleteLater();
        m_pReply = nullptr;
    }
    m_DownloadFile.close();
    ui->progressBar->hide();
    emit sigDownloadFinished();
}

void CFrmUpdater::slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBar->setRange(0, static_cast<int>(bytesTotal));
    ui->progressBar->setValue(static_cast<int>(bytesReceived));
}

void CFrmUpdater::slotError(QNetworkReply::NetworkError e)
{
    qDebug() << "CFrmUpdater::slotError: " << e;
    ui->lbState->setText(tr("Download network error: ")
                         + m_pReply->errorString());
    if(m_pReply)
    {
        m_pReply->disconnect();
        m_pReply->deleteLater();
        m_pReply = nullptr;
    }
    ui->progressBar->hide();
    m_DownloadFile.close();
    emit sigError();
}

void CFrmUpdater::slotSslError(const QList<QSslError> e)
{
    qDebug() << "CFrmUpdater::slotSslError: " << e;
    QString sErr;
    foreach(QSslError s, e)
        sErr += s.errorString() + " ";
    ui->lbState->setText(tr("Download fail:") + sErr);
    if(m_pReply)
    {
        m_pReply->disconnect();
        m_pReply->deleteLater();
        m_pReply = nullptr;
    }
    ui->progressBar->hide();
    m_DownloadFile.close();
    emit sigError();
}

void CFrmUpdater::slotCheck()
{
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    QDateTime d = set.value("Update/DateTime").toDateTime();
    set.setValue("Update/DateTime", QDateTime::currentDateTime());
    if(m_bDownload)
    {
        emit sigFinished();
        return;
    }

    int n = 0;
    if(ui->rbEveryDate->isChecked())
        n = 1;
    else if(ui->rbEveryWeek->isChecked())
        n = 7;
    else if(ui->rbEveryMonth->isChecked())
        n = 30;

    if(n <= d.daysTo(QDateTime::currentDateTime()))
        emit sigFinished();
    else
        emit sigError();
}

void CFrmUpdater::slotDownloadXmlFile()
{
    if(m_Url.isValid())
        DownloadFile(m_Url);
}

/*
   <?xml version="1.0" encoding="UTF-8"?>
   <UPDATE>
    <VERSION>v0.0.1</VERSION>
    <TIME>2019-2-24 19:28:50</TIME>
    <INFO>v0.0.1 information</INFO>
    <FORCE>0</FORCE>
    <SYSTEM>Windows</SYSTEM>
    <PLATFORM>x86</PLATFORM>
    <ARCHITECTURE>x86</ARCHITECTURE>
    <URL>url</URL>
    <MD5SUM>%RABBITIM_MD5SUM%</MD5SUM>
    <MIN_UPDATE_VERSION>%MIN_UPDATE_VERSION%</MIN_UPDATE_VERSION>
   </UPDATE>
 */
void CFrmUpdater::slotDownload()
{
    qDebug() << "CFrmUpdater::slotDownload()";
    if(!m_DownloadFile.open(QIODevice::ReadOnly))
    {
        emit sigError();
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&m_DownloadFile))
    {
        QString szError = tr("Parse file %1 fail. It isn't xml file")
                .arg(m_DownloadFile.fileName());
        ui->lbState->setText(szError);
        m_DownloadFile.close();
        emit sigError();
        return;
    }
    m_DownloadFile.close();
    
    QDomNodeList lstNode = doc.documentElement().childNodes();
    for(int i = 0; i < lstNode.length(); i++)
    {
        QDomElement node = lstNode.item(i).toElement();
        if(node.nodeName() == "VERSION")
            m_Info.szVerion = node.text();
        else if(node.nodeName() == "TIME")
            m_Info.szTime = node.text();
        else if(node.nodeName() == "INFO")
            m_Info.szInfomation = node.text();
        else if(node.nodeName() == "FORCE")
            m_Info.bForce = node.text().toInt();
        else if(node.nodeName() == "SYSTEM")
            m_Info.szSystem = node.text();
        else if(node.nodeName() == "PLATFORM")
            m_Info.szPlatform = node.text();
        else if(node.nodeName() == "ARCHITECTURE")
            m_Info.szArchitecture = node.text();
        else if(node.nodeName() == "URL")
            m_Info.szUrl = node.text();
        else if(node.nodeName() == "MD5SUM")
            m_Info.szMd5sum = node.text();
        else if(node.nodeName() == "MIN_UPDATE_VERSION")
            m_Info.szMinUpdateVersion = node.text();
    }
    qDebug() << "version: " << m_Info.szVerion
             << "time: " << m_Info.szTime
             << "bForce: " << m_Info.bForce
             << "system: " << m_Info.szSystem
             << "Platform: " << m_Info.szPlatform
             << "Arch: " << m_Info.szArchitecture
             << "url: " << m_Info.szUrl
             << "md5: " << m_Info.szMd5sum
             << "minUpdateVersion: " << m_Info.szMinUpdateVersion;
    if(CompareVersion(m_Info.szVerion, m_szCurrentVersion) <= 0)
    {
        ui->lbState->setText(tr("There is laster version"));
        emit sigFinished();
        return;
    }
    
    ui->lbNewVersion->setText(tr("New version: %1").arg(m_Info.szVerion));
    ui->lbNewVersion->show();
    ui->lbNewArch->setText(tr("New architecture: %1").arg(m_Info.szArchitecture));
    ui->lbNewArch->show();
    
#if defined (Q_OS_WIN)
    if(m_Info.szSystem.compare("windows", Qt::CaseInsensitive))
    {
        emit sigFinished();
        return;
    }
#elif defined(Q_OS_ANDROID)
    if(m_Info.szSystem.compare("android", Qt::CaseInsensitive))
    {
        emit sigFinished();
        return;
    }
#elif defined (Q_OS_LINUX)
    if(m_Info.szSystem.compare("linux", Qt::CaseInsensitive))
    {
        emit sigFinished();
        return;
    }
#endif   

    ui->lbState->setText(tr("There is a new version, is it updated?"));
    if(m_Info.bForce)
        DownloadFile(m_Info.szUrl);
    else
    {
        ui->pbOK->show();
        show();
    }
}

void CFrmUpdater::slotUpdate()
{
    ui->lbState->setText(tr("Being install update ......"));
    qDebug() << "CFrmUpdater::slotUpdate()";
    if(!m_DownloadFile.open(QIODevice::ReadOnly))
    {
        qCritical() << "Download file fail: " << m_DownloadFile.fileName();
        ui->lbState->setText(tr("Download file fail"));
        emit sigError();
        return;
    }
    QCryptographicHash md5sum(QCryptographicHash::Md5);
    if(!md5sum.addData(&m_DownloadFile))
    {
        ui->lbState->setText(tr("Download file fail"));
        emit sigError();
        return;
    }
    if(md5sum.result().toHex() != m_Info.szMd5sum)
    {
        QString szFail;
        szFail = tr("Md5sum is different. ")
                    + "\n" + tr("down file md5sum: ")
                    + md5sum.result().toHex()
                    + "\n" + tr("md5sum in Update.xml:")
                    + m_Info.szMd5sum;
        ui->lbState->setText(szFail);
        emit sigError();
        return;
    }
    QProcess::execute(m_DownloadFile.fileName());
    emit sigFinished();
    //TODO: Wether quit application?
}

int CFrmUpdater::CompareVersion(const QString &newVersion, const QString &currentVersion)
{
    int nRet = 0;
    QStringList szNew = newVersion.split(".");
    QStringList szCur = currentVersion.split(".");
    if(szNew.at(0).toInt() > szCur.at(0).toInt())
        return 1;
    else if(szNew.at(0).toInt() < szCur.at(0).toInt()){
        return -1;
    }
    if(szNew.at(1).toInt() > szCur.at(1).toInt())
        return 1;
    else if(szNew.at(1).toInt() < szCur.at(1).toInt()){
        return -1;
    }
    if(szNew.at(2).toInt() > szCur.at(2).toInt())
        return 1;
    else if(szNew.at(2).toInt() < szCur.at(2).toInt()){
        return -1;
    }
    return nRet;
}

void CFrmUpdater::on_pbOK_clicked()
{
    DownloadFile(m_Info.szUrl);
    ui->pbOK->hide();
    ui->lbState->setText(tr("Download ......"));
}

void CFrmUpdater::on_pbClose_clicked()
{
    close();
}

void CFrmUpdater::slotButtonClickd(int id)
{
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(), QSettings::IniFormat);
    set.setValue("Update/RadioButton", id);
}
