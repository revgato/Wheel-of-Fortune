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
    static std::string server_ip;
    static int server_port;
    explicit Backend(QObject *parent = nullptr);
    Q_INVOKABLE void connectToServer();
    
signals:
    void connectedToServer();
    void connectionFailed();
};

#endif // BACKEND_H
