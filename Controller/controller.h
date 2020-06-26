#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Controller_global.h"
#include <mpd/client.h>
#include <QObject>
#include <QSocketNotifier>

class CONTROLLER_EXPORT Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    enum class ConnectionState { Disconnected, Connecting, Connected };
    Q_ENUM(ConnectionState)
public slots:
    void handleListAlbumsClick();
    void connectToMPD(QString, int, int);

public:
    QVector<QString> getAlbumList();

    QString defaultHost();
    unsigned defaultPort();

    ConnectionState connectionState() const;
    void setConnectionState(ConnectionState);

signals:
    void errorMessage(QString);
    void connectionStateChanged(Controller::ConnectionState connectionState);

    void beginMPDCommand();
    void endMPDCommand();

    void unrecoverableError();

    void queueChanged();

private:
    void handleIdle(mpd_idle);
    void createMPD(QString, int, int);

    QString m_defaultHost;
    unsigned m_defaultPort;
    unsigned m_defaultTimeout;

    mpd_connection *m_connection;
    QSocketNotifier *m_notifier;

    unsigned m_queueVersion;

    ConnectionState m_connectionState;

private slots:
    void handleActivation();
};

Q_DECLARE_METATYPE(Controller::ConnectionState);

#endif // CONTROLLER_H
