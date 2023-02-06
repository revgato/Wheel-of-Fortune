#ifndef BACKEND_H
#define BACKEND_H
#include <QObject>

extern "C" {
    #include "utils.h"
}


class Backend : public QObject
{
    Q_OBJECT
    // Property an array of QString
    Q_PROPERTY(QStringList textList READ getTextList)
    // Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)

public:
    static char server_ip[16];
    static int server_port;
    // static QString text;
    static QStringList textList;
    explicit Backend(QObject *parent = nullptr);
    // QString getText() const;
    QStringList getTextList() const;
    void setText(QString value);
    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void join(QString username_input);
    
    
signals:
    void connectedToServer();
    void connectionFailed();
    void waitingRoom();
    void refuse();
    void gameStart();
};

#endif // BACKEND_H
