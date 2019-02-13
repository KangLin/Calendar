#ifndef FRMUPDATER_H
#define FRMUPDATER_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>

namespace Ui {
class CFrmUpdater;
}

class CFrmUpdater : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmUpdater(QWidget *parent = nullptr);
    ~CFrmUpdater();
    
    int StartDownload(const QString szUrl);
    
private Q_SLOTS:
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError e);
    void slotSslError(const QList<QSslError> e);
    void slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void slotFinished();
    
private:
    Ui::CFrmUpdater *ui;
    
    QNetworkAccessManager m_NetManager;
    QFile m_DownloadFile;
    QNetworkReply *m_pReply;
};

#endif // FRMUPDATER_H
