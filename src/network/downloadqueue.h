#ifndef NETWORK_H
#define NETWORK_H

#include "queueinfo.h"
#include "network_global.h"
class DownloadQueue : public QObject
{
    Q_OBJECT
public:
    explicit DownloadQueue();

    static DownloadQueue *initialize();

    void StartQueue();

    void add(QueueInfo *info);

    bool exists(QueueInfo *info);

    bool DownloadSingle(QUrl url, QString filepath, QueueInfo *info);

    static bool isHttpRedirect(QNetworkReply *reply);

    static DownloadQueue *instance;

signals:
    void OnEnqueue(QueueInfo *info);
    void OnDequeue(QueueInfo *info);
    void QueueFinished(QList<QueueInfo*> history);
    void DownloadProgress(qint64 received, qint64 total, QElapsedTimer time);

public slots:
    void progress(qint64 received, qint64 total);

private:
    QList<QueueInfo*> history;
    QQueue<QueueInfo*> queue;
    QElapsedTimer downloadTime;
};

#endif // NETWORK_H
