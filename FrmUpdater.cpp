#include "FrmUpdater.h"
#include "ui_FrmUpdater.h"
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QStandardPaths>
#include <QFinalState>
#include <QDomDocument>
#include <QDomText>
#include <QDomElement>
#include <QProcess>
#include <QDir>

CFrmUpdater::CFrmUpdater(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmUpdater),
    m_NetManager(this),
    m_pReply(nullptr)
{
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);
    ui->lbNewArch->hide();
    ui->lbNewVersion->hide();
    ui->progressBar->hide();
    ui->pbOK->hide();
    SetTitle(qApp->applicationDisplayName());
    
    SetArch(BUILD_ARCH);
    SetVersion(BUILD_VERSION);
    
    QFinalState *sFinal = new QFinalState();
    QState *s = new QState();
    s->addTransition(this, SIGNAL(sigError()), sFinal);
    s->addTransition(this, SIGNAL(sigFinished()), sFinal);
    m_StateMachine.addState(s);
    m_StateMachine.addState(sFinal);
    
    QState *sDownloadXmlFile = new QState(s);
    QState *sDownload = new QState(s);
    QState *sUpdate = new QState(s);
    s->setInitialState(sDownloadXmlFile);
    sDownloadXmlFile->addTransition(this, SIGNAL(sigDownloadFinished()), sDownload);
    sDownload->addTransition(this, SIGNAL(sigDownloadFinished()), sUpdate);
    sDownloadXmlFile->assignProperty(ui->lbState, "text", tr("Being download xml file"));
    sDownload->assignProperty(ui->lbState, "text", tr("Being download update file"));
    sUpdate->assignProperty(ui->lbState, "text", tr("Being install update"));
    bool check = connect(sDownloadXmlFile, SIGNAL(entered()),
                         this, SLOT(slotDownloadXmlFile()));
    Q_ASSERT(check);
    check = connect(sDownload, SIGNAL(entered()), this, SLOT(slotDownload()));
    Q_ASSERT(check);
    check = connect(sUpdate, SIGNAL(entered()), this, SLOT(slotUpdate()));
    Q_ASSERT(check);
    m_StateMachine.setInitialState(s);
    m_StateMachine.start();
}

CFrmUpdater::~CFrmUpdater()
{
    delete ui;
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

int CFrmUpdater::DownloadFile(const QUrl &url)
{
    int nRet = 0;
    if(!m_StateMachine.isRunning())
    {
        m_Url = url;
        return 0;
    }
    
    if(url.isLocalFile())
    {
        m_DownloadFile.setFileName(url.toLocalFile());
        emit sigDownloadFinished();
        return 0;
    }
    
    QString szTmp = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    szTmp = szTmp + QDir::separator() + "Rabbit" + QDir::separator() + qApp->applicationName();
    QDir d;
    if(!d.exists(szTmp))
        d.mkpath(szTmp);
    QString szPath = url.path();   
    QString szFile = szTmp + szPath.mid(szPath.lastIndexOf("/"));
    m_DownloadFile.setFileName(szFile);
    if(!m_DownloadFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Open file fail: " << szFile;
        return -1;
    }

    QNetworkRequest request(url);
    m_pReply = m_NetManager.get(request);
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
    if(m_pReply)
    {
        m_pReply->disconnect();
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
        m_pReply = nullptr;
    }
    ui->progressBar->hide();
    m_DownloadFile.close();
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
 * 
 * 
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
        qDebug() << "Parse file " << m_DownloadFile.fileName()
                 << "fail. It isn't xml file";
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
        emit sigFinished();
        return;
    }
    
    ui->lbNewVersion->setText(tr("New version: %1").arg(m_Info.szVerion));
    ui->lbNewVersion->show();
    ui->lbNewArch->setText(tr("New architecture: %1").arg(m_Info.szArchitecture));
    ui->lbNewArch->show();
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
        szFail = "md5sum fail. down file md5sum: "
                    + md5sum.result().toHex()
                    + "; md5sum in Update.xml:"
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
