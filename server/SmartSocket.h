#ifndef SMARTSOCKET_H
#define SMARTSOCKET_H

#include <QObject>
#include <QAbstractSocket>

class SmartSocket : public QObject
{
        Q_OBJECT
    public:
        explicit SmartSocket(QAbstractSocket* parent = 0);
        QAbstractSocket* getSocket() {return socket;}
    signals:
        void lineReceived(SmartSocket*, const QString&);
        void disconnected(SmartSocket*);

    protected slots:
        void slot_disconnected();
        void slot_data_available();
    protected:
        QAbstractSocket* socket;
        QByteArray buffer;
};

#endif // SMARTSOCKET_H
