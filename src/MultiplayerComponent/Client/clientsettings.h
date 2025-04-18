#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

#include <QHostAddress>

class ClientSettings
{
public:
    ClientSettings() {}

    //! Gets the broadcast port.
    quint16 GetBroadcastPort() const;

    //! Sets the broadcast port.
    void SetBroadcastPort(quint16 broadcastPort);

    //! Gets the TTC (Time to close) value in [ms].
    int GetTTC() const;

    //! Sets the TTC (Time to close) value in [ms] that represet how long
    //! server stay active, until next broadcast message came.
    void SetTTC(int ttc);

    QString GetClientName() const;
    void SetClientName(const QString &clientName);

private:

    quint16 _broadcastPort = 0;

    //! Default value is 3 [ms].
    int _ttc = 3;

    QString _clientName;
};

#endif // CLIENTSETTINGS_H
