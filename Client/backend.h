#ifndef BACKEND_H
#define BACKEND_H
#include <QObject>

extern "C" {
    #include "utils.h"
}


class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)

public:
    static char server_ip[16];
    static int server_port;
    static QString text;
    explicit Backend(QObject *parent = nullptr);
    QString getText() const;
    void setText(QString value);
    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void join(QString username_input);
    
signals:
    void textChanged();
    void connectedToServer();
    void connectionFailed();
    void waitingRoom();
    void refuse();
};

#endif // BACKEND_H
