#ifndef BACKEND_H
#define BACKEND_H
#include <QObject>

extern "C"
{
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
    static Backend *instance;
    // static QString text;
    static QStringList textList;
    explicit Backend(QObject *parent = nullptr);
    ~Backend();
    // QString getText() const;
    QStringList getTextList() const;
    void setText(QString value);
    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void join(QString username_input);
    Q_INVOKABLE void updateWaitingRoom();
    Q_INVOKABLE void updateGameState();
    Q_INVOKABLE void updateNotification();
    Q_INVOKABLE void startGame();
    Q_INVOKABLE void exitGame();
    // void *pthread_waiting_room(void *arg);

signals:
    void connectedToServer();
    void connectionFailed();
    void waitingRoom();
    void refuse();
    void gameState();
    void userJoined();
    void updateGameStateSignal();
    void updateNotificationSignal();
    void gameStart();
    void notification();
};

void *pthread_waiting_room(void *arg);
void *pthread_game_state(void *arg);

#endif // BACKEND_H
