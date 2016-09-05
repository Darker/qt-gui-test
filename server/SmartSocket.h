#ifndef SMARTSOCKET_H
#define SMARTSOCKET_H

#include <QObject>
#include <QAbstractSocket>
class QTextCodec;
class SmartSocket : public QObject
{
        Q_OBJECT
    public:
        explicit SmartSocket(QAbstractSocket* parent = 0);
        QAbstractSocket* getSocket() {return socket;}
        QString getName() const;

        void setName(const QString& value);

    signals:
        void lineReceived(SmartSocket*, const QString&);
        void disconnected(SmartSocket*);
    public slots:
        void writeln(const QString&);
        QByteArray encodeString(const QString&) const;
    protected slots:
        void slot_disconnected();
        void slot_data_available();
    protected:
        QAbstractSocket* socket;
        // Used by server for identification
        QString name;
        const QTextCodec* encoding;
        QByteArray buffer;
        // Allows user to recall previous commands
        QStringList history;
        int history_pos;
        bool hasHistory() const {return history.length()>0;}
        bool escReceived;
        bool controlReceived;
        // Converts buffer to qstring and emits lineReceived
        // clears buffer
        void handleNewLine();

        void historyAdd( const QString& );
        const QString& historyRetrieve();
};

#endif // SMARTSOCKET_H
