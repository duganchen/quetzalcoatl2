#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Controller_global.h"
#include "songitem.h"
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

    QVector<QString> getAlbumList();

    QString defaultHost();
    unsigned defaultPort();

    QSocketNotifier *notifier() const;
    mpd_connection *mpd() const;
public slots:
    void handleListAlbumsClick();
    void connectToMPD(QString, int, int);

    void updateStatus();

    void moveSongs(QVector<unsigned>, unsigned);
signals:
    void errorMessage(QString);
    void connectionState(Controller::ConnectionState connectionState);

    void beginMPDCommand();
    void endMPDCommand();

    void unrecoverableError();

    void connectionErrorMessage(QString);

    void sliderMax(int);
    void sliderValue(int);

    void statusMessage(QString, int);

    void shuffled(bool);
    void repeating(bool);
    void crossfade(int);
    void volume(int);

    void queueChanged(const QVector<SongItem *> &);

private:
    void handleIdle(mpd_idle);
    void createMPD(QString, int, int);

    void enableIdle();
    void disableIdle();

    void pollForStatus();

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