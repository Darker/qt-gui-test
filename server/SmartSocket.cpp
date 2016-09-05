#include "SmartSocket.h"
#include "ANSI.h"
#include <QDebug>
#include <QTextCodec>
SmartSocket::SmartSocket(QAbstractSocket *parent) :
    QObject(parent)
  , socket(parent)
  , history_pos(0)
  , controlReceived(false)
  , escReceived(true)
  , encoding(nullptr)
{
    QObject::connect(parent, &QAbstractSocket::disconnected,
                     this, &SmartSocket::slot_disconnected);
    QObject::connect(parent, &QAbstractSocket::readyRead,
                     this, &SmartSocket::slot_data_available);
}

void SmartSocket::writeln(const QString& ln)
{
    socket->write(SmartSocket::encodeString(ln+"\r\n"));
    socket->flush();
}

QByteArray SmartSocket::encodeString(const QString& str) const
{
    if(encoding == nullptr)
        return str.toUtf8();
    else
        return encoding->fromUnicode(str);
}

void SmartSocket::slot_disconnected()
{
    emit disconnected(this);
}

void SmartSocket::slot_data_available()
{
    QByteArray data = socket->readAll();
    QString string("");
    if(encoding != nullptr)
        string = encoding->toUnicode(data);
    else
        string = QString::fromUtf8(data);

    for(int i=0,l=string.length(); i<l; i++) {
       QChar oneByte = string[i];
       // Will be set to true to prevent adding this to buffer
       bool consumed = false;
       if(oneByte == '\n') {
           consumed = true;
           handleNewLine();
       }
       else if (oneByte == 8) {
           consumed = true;
           if(buffer.length()>0) {
               buffer.remove(buffer.length()-1, 1);
               QByteArray data;
               data.append(' ');
               data.append((char)8);
               socket->write(data);
               // " "+String.valueOf((char)8)
           }
       }
       else if(oneByte=='\r') {
           // ignored atm
           consumed = true;
       }
       if(controlReceived) {
           consumed = true;
           controlReceived = false;
           if(oneByte == ANSI::UP && hasHistory()) {
               QByteArray data;
               data.append(ANSI::RETURN);
               data.append("                                           ");
               data.append(ANSI::RETURN);
               const QString& str = historyRetrieve();
               data.append(encodeString(str));
               socket->write(data);
               buffer.clear();
               buffer.append(str);
           }
       }
       if(oneByte==ANSI::ESC) {
           escReceived = true;
           consumed = true;
       }

       if(escReceived && oneByte==ANSI::BEGIN_CONTROL) {
           controlReceived = true;
           escReceived = false;
           consumed = true;
       }

       if(!consumed) {
           buffer.append(oneByte);
           escReceived = false;
           controlReceived = false;
       }


       //qDebug()<<(int)oneByte<<buffer;
    }
}

void SmartSocket::setName(const QString& value)
{
    name = value;
}

QString SmartSocket::getName() const
{
    return name;
}

void SmartSocket::handleNewLine()
{
    const QString line = QString::fromUtf8(buffer);
    if(line.startsWith("encoding ")) {
        const QString encName = line.mid(9);
        if(encName=="win" ||
                encName=="windows" ||
                encName=="windoze") {
            encoding = QTextCodec::codecForName("CP-1252");
        }
        else if(encName=="list") {
            QList<QByteArray> codecs(QTextCodec::availableCodecs());
            const QTextCodec*const originalEncoding = encoding;
            const QString testString(QString(": ěščřžýáíé"));
            Q_FOREACH(QByteArray codecName, codecs) {
                encoding = QTextCodec::codecForName(codecName);
                writeln(QString::fromUtf8(codecName)+testString);
            }
            encoding = originalEncoding;
        }
        else if(encName=="default") {
            encoding = nullptr;
        }
        else {
            encoding = QTextCodec::codecForName(encName.toStdString().c_str());
        }
    }
    else {
        emit lineReceived(this, line);
    }
    buffer.clear();
    historyAdd(line);
}

void SmartSocket::historyAdd(const QString& line)
{
    history.prepend(line);
    history_pos = 0;
}

const QString& SmartSocket::historyRetrieve()
{
    if(history_pos>=history.length()) {
        history_pos-=history.length();
    }
    int offset = history_pos++;
    return history[offset];
}
