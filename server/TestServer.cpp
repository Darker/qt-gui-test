#include "TestServer.h"
#include <QTcpSocket>


TestServer::TestServer(const quint16 port, const QHostAddress addr, QObject* parent)
  : QObject(parent)
  , client_id(0)
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, &QTcpServer::newConnection, this, &TestServer::newConnection);

    if(!server->listen(addr, port))
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
    // get or generate transaction id
    QString transactionId = "";

    int idDelimiter = cmd.indexOf(",");
    if(idDelimiter!=-1) {
        transactionId = cmd.left(idDelimiter);
        cmd = cmd.mid(idDelimiter+1);
    }
    else {
        static uint32_t ID = 0;
        transactionId = QString("trans_")+QString::number(++ID);
    }
    // add client ID to transaction ID
    transactionId = QString("client_%1_%2").arg(socket->getName()).arg(transactionId);

    emit command(cmd, params, transactionId);
}

void TestServer::disconnected(SmartSocket* socket)
{
    sockets.removeAll(socket);
    /*int pos = -1;
    if( (pos = sockets.indexOf(socket)) != -1) {
        sockets.

    }*/
}

void TestServer::message(const QString message, const QString transactionId)
{
    bool priv = !transactionId.isEmpty();
    for (int i=0,l=sockets.size(); i<l; i++)
    {
        SmartSocket*const socket = sockets[i];

        if(priv) {
            const QString prefix("client_"+socket->getName()+"_");
            if(transactionId.startsWith(prefix)) {
                QString realId = transactionId.mid(prefix.length());
                socket->writeln(realId+","+message);
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
QString qvariant2JSON(const QVariant& data) {
    QString output("");
    if(data.canConvert<QVariantList>()) {
        output+="[";
        const QVariantList list = data.value<QVariantList>();
        Q_FOREACH(const QVariant& entry, list) {
            if(output.length()>1)
                output+=",";
            output+=qvariant2JSON(entry);
        }
    }
    else if(data.canConvert<QString>())
        return '"'+data.toString()+'"';
    else
        return "";

}

void TestServer::message(const QVariant message, const QString transactionId)
{
    this->message(qvariant2JSON(message), transactionId);
}

void TestServer::message(const QString message)
{
    this->message(message, "");
}
