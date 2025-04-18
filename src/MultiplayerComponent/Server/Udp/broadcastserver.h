#ifndef BROADCASTSERVER_H
#define BROADCASTSERVER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QUdpSocket>
#include <QUuid>

class BroadcastServer : public QObject
{
    Q_OBJECT
public:
    BroadcastServer();
    BroadcastServer(const QUuid& guid);

    //! Sends data to given address and port.
    //!
    //! @param address Destination address.
    //! @param port Destination port.
    //! @param data Data to sent.
    void SendData(const QHostAddress& address, quint16 port, const QByteArray& data);

    //! Starts sending data to given address and port frequently.
    //!
    //! @param address Destination address.
    //! @param port Destination port.
    //! @param data Data to sent (json format).
    //! @param interval Time in millicesonds [ms].
    void StartSendingData(const QHostAddress& address, quint16 port, const QJsonObject& data, int interval);

    //! Stops the sending data.
    void StopSendingData();

    //! Changes the value based on the key of data to send.
    //!
    //! @param key Existing key in the data.
    //! @param value New value.
    void ChangeData(const QString& key, const QJsonValue& value);

private:
    void TimerTimeout();

private:
    QTimer _timer;
    QUuid _guid;

    //! Data to send in loop
    struct DataToSend
    {
        QHostAddress address;
        quint16 port = 0;
        QByteArray data;
    };

    DataToSend _dataToSend;
};

#endif // BROADCASTSERVER_H
