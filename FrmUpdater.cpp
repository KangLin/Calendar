#include "FrmUpdater.h"
#include "ui_FrmUpdater.h"
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QStandardPaths>

CFrmUpdater::CFrmUpdater(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmUpdater),
    m_NetManager(this),
    m_pReply(NULL)
{
    ui->setupUi(this);
}

CFrmUpdater::~CFrmUpdater()
{
    delete ui;
}

int CFrmUpdater::StartDownload(const QString szUrl)
{
    int nRet = 0;
    QString szFile;
    QStringList f = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
    szFile = f.at(0) + "/Updater-" + QDateTime::currentDateTime().toString("yyyy-MM-dd.HH-mm-ss.zzz");
        
    m_DownloadFile.setFileName(szFile);
    if(!m_DownloadFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Open file fail: " << szFile;
        return -1;
    }
    
    QUrl url(szUrl);
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
    return nRet;
}

void CFrmUpdater::slotFinished()
{
    qDebug() << "CFrmUpdater::slotFinished()";
    if(m_pReply)
    {
        m_pReply->disconnect();
        m_pReply = NULL;
    }
    m_DownloadFile.close();
}

void CFrmUpdater::slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBar->setRange(0, bytesTotal);
    ui->progressBar->setValue(bytesReceived);
}

void CFrmUpdater::slotError(QNetworkReply::NetworkError e)
{
    qDebug() << "CFrmUpdater::slotError: " << e;
}

void CFrmUpdater::slotSslError(const QList<QSslError> e)
{
}

void CFrmUpdater::slotReadyRead()
{
    qDebug() << "CFrmUpdater::slotReadyRead()";
    if(m_DownloadFile.isOpen() && m_pReply)
    {
        QByteArray d = m_pReply->readAll();
        qDebug() << d;
        m_DownloadFile.write(d);
    }
}
