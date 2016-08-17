#ifndef TESTSERVER_H
#define TESTSERVER_H

#include <QObject>
#include <QTcpServer>
#include "SmartSocket.h"

class TestServer : public QObject
{
        Q_OBJECT
    public:
        explicit TestServer(QObject *parent = 0);

    signals:
        void command(const QString& command, const QString& params);
    public slots:
        void newConnection();
        void lineReceived(SmartSocket* socket, const QString& data);
        void disconnected(SmartSocket* socket);
    protected:
        QList<SmartSocket*> sockets;
        QTcpServer *server;
};

#endif // TESTSERVER_H
