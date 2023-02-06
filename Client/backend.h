#ifndef BACKEND_H
#define BACKEND_H
#include <QObject>

extern "C" {
    #include "utils.h"
}

class Backend : public QObject
{
    Q_OBJECT

public:
    static char server_ip[16];
    static int server_port;
    explicit Backend(QObject *parent = nullptr);
    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void join(QString const username_input);
    
signals:
    void connectedToServer();
    void connectionFailed();
    void waitingRoom();
    void refuse();
};

#endif // BACKEND_H
