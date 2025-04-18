#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <QHostAddress>

class ServerSettings
{
public:
    ServerSettings() {};

    //! Gets the TTS (time to send) new message in loop.
    int GetTTS() const;

    //! Sets the TTS (time to send) new message in loop.
    void SetTTS(int tts);

    //! Gets the interval of sending discovery mesages.
    int GetDiscoveryInterval() const;

    //! Sets the interval of sending discovery mesages.
    void SetDiscoveryInterval(int discoveryInterval);

    //! Gets the broadcast port.
    quint16 GetBroadcastPort() const;

    //! Sets the broadcast port.
    void SetBroadcastPort(quint16 broadcastPort);

    //! Gets the port.
    quint16 GetPort() const;

    //! Sets the port.
    void SetPort(quint16 port);

    //! Gets the max players.
    int32_t GetMaxPlayers() const;

    //! Sets the max players.
    void SetMaxPlayers(int32_t maxPlayers);

    //! Gets the name of the server.
    QString GetServerName() const;

    //! Sets the name of the server.
    void SetServerName(const QString& serverName);

private:

    // Braodcast settings
    int _tts = 0;
    int _discoveryInterval = 300;
    quint16 _broadcastPort = 0;
    QHostAddress _broadcastAddress;

    // Server settings
    quint16 _port = 0;
    int32_t _maxPlayers = 10;
    QString _serverName = "Default server";
};

#endif // SERVERSETTINGS_H
