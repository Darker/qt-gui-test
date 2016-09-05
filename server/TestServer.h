#ifndef TESTSERVER_H
#define TESTSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include "SmartSocket.h"

class TestServer : public QObject
{
        Q_OBJECT
    public:
        explicit TestServer(const quint16 port=9666, const QHostAddress addr = QHostAddress::Any, QObject *parent = 0);

    signals:
        void command(const QString& command, const QString& params);
    public slots:
        void newConnection();
        void lineReceived(SmartSocket* socket, const QString& data);
        void disconnected(SmartSocket* socket);
        //void messageForClient(const int clientId, const QString message);
        void message(const QString message);
    protected:
        QList<SmartSocket*> sockets;
        QTcpServer *server;
        unsigned int client_id;
};

#endif // TESTSERVER_H
