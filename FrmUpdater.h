#ifndef FRMUPDATER_H
#define FRMUPDATER_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QPixmap>
#include <QApplication>
#include <QStateMachine>
#include <QUrl>

namespace Ui {
class CFrmUpdater;
}

class CFrmUpdater : public QWidget
{
    Q_OBJECT

public:
    explicit CFrmUpdater(QWidget *parent = nullptr);
    virtual ~CFrmUpdater();

    int DownloadFile(const QUrl &url);
    int SetVersion(const QString &szVersion);
    int SetArch(const QString &szArch);
    int SetTitle(const QString &szTitle, QPixmap icon = QPixmap());

private Q_SLOTS:
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError e);
    void slotSslError(const QList<QSslError> e);
    void slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void slotFinished();

    void slotDownloadXmlFile();
    void slotDownload();
    void slotUpdate();

    void on_pbOK_clicked();
    void on_pbClose_clicked();
    
Q_SIGNALS:
    void sigError();
    void sigFinished();
    void sigDownloadFinished();

private:
    int CompareVersion(const QString &newVersion, const QString &currentVersion);

private:
    Ui::CFrmUpdater *ui;

    QString m_szCurrentVersion;
    QString m_szCurrentArch;

    QUrl m_Url;
    QFile m_DownloadFile;
    QNetworkAccessManager m_NetManager;
    QNetworkReply *m_pReply;

    QStateMachine m_StateMachine;

    struct INFO{
        QString szVerion;
        QString szInfomation;
        QString szTime;
        bool bForce;
        QString szSystem;
        QString szPlatform;
        QString szArchitecture;
        QString szUrl;
        QString szMd5sum;
        QString szMinUpdateVersion;
    } m_Info;
};

#endif // FRMUPDATER_H
