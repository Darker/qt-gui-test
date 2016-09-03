#include "TestServer.h"
#include <QTcpSocket>

TestServer::TestServer(QObject *parent) : QObject(parent)
  , client_id(0)
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, &QTcpServer::newConnection, this, &TestServer::newConnection);

    if(!server->listen(QHostAddress::Any, 9666))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }
}
void TestServer::newConnection()
{
    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("TESTING LINE OK\r\n");
    socket->flush();

    SmartSocket* s = new SmartSocket(socket);
    s->setName(QString::number(++client_id));
    sockets.push_back(s);
    connect(s, &SmartSocket::lineReceived, this, &TestServer::lineReceived);
    connect(s, &SmartSocket::disconnected, this, &TestServer::disconnected);
}

void TestServer::lineReceived(SmartSocket* socket, const QString& data)
{
    if(data.startsWith("exit")) {
        socket->getSocket()->close();
    }
    int index = data.indexOf("::");
    QString cmd;
    QString params;

    if(index == -1) {
        cmd = data;
        params = "";
    }
    else {
        cmd = data.left(index);
        params = data.mid(index+2);
    }
    // Tmp fix to make reply messages different for each client
    // otherwise clients receive other client's replies
    if(cmd == "wait" || cmd=="coords") {
        QStringList l = params.split("::");
        if(l.length()>1) {
            l[1] = QString("client_%1_%2").arg(socket->getName()).arg(l[1]);
            params = l.join("::");
        }
    }

    emit command(cmd, params);
}

void TestServer::disconnected(SmartSocket* socket)
{
    sockets.removeAll(socket);
    /*int pos = -1;
    if( (pos = sockets.indexOf(socket)) != -1) {
        sockets.

    }*/
}

void TestServer::message(const QString message)
{
    bool priv = message.startsWith("client_");
    for (int i=0,l=sockets.size(); i<l; i++)
    {
        SmartSocket*const socket = sockets[i];

        if(priv) {
            const QString prefix("client_"+socket->getName()+"_");
            if(message.startsWith(prefix)) {
                QString realMsg = message.mid(prefix.length());
                socket->writeln(realMsg);
                break;
            }
        }
        else {
            socket->writeln(message);
        }
    }
    /*for(SmartSocket* s: sockets) {
        s->writeln(message);
    }*/
}
