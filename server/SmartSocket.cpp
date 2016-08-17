#include "SmartSocket.h"

SmartSocket::SmartSocket(QAbstractSocket *parent) :
    QObject(parent)
  , socket(parent)
{
    QObject::connect(parent, &QAbstractSocket::disconnected,
                     this, &SmartSocket::slot_disconnected);
    QObject::connect(parent, &QAbstractSocket::readyRead,
                     this, &SmartSocket::slot_data_available);
}

void SmartSocket::slot_disconnected()
{
    emit disconnected(this);
}

void SmartSocket::slot_data_available()
{
    QByteArray data = socket->readLine(0);
    buffer.append(data);

    int index = -1;
    if( ( index = buffer.indexOf('\r')) != -1 ||
        ( index = buffer.indexOf('\n')) != -1 ) {

        const QString line = QString::fromUtf8(buffer.mid(0, index));
        emit lineReceived(this, line);

        buffer.remove(0, line.length()+1);
        while(buffer.length()>0 && (buffer[0]=='\n' || buffer[0]=='\r')) {
            buffer.remove(0,1);
        }
    }
}
