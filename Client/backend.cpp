extern "C"
{
#include "utils.h"
}
#include "backend.h"

extern conn_msg_type conn_msg;
extern char username[50];
extern int bytes_received;
Backend *Backend::instance = nullptr;

// pthread_mutex_t lock;

// QString Backend::text = "";
QStringList Backend::textList;
char Backend::server_ip[16];
int Backend::server_port = 5500;

Backend::Backend(QObject *parent) : QObject(parent)
{
    if (Backend::instance == nullptr)
    {
        Backend::instance = this;
    }
}

Backend::~Backend()
{
    delete Backend::instance;
}

void Backend::connectToServer()
{
    // pthread_mutex_init(&lock, NULL);

    if (connect_to_server(Backend::server_ip, Backend::server_port) == 1)
    {
        emit connectedToServer();
    }
    else
    {
        emit connectionFailed();
    }
}

void Backend::join(QString username_input)
{
    strcpy(username, username_input.toStdString().c_str());
    conn_msg.data.player = init_player(username, -1);
    conn_msg.type = JOIN;
    send_server();
    receive_server();
    pthread_t tid;

    if (conn_msg.type == WAITING_ROOM)
    {
        for (int i = 0; i < conn_msg.data.waiting_room.joined; i++)
        {
            textList.append(conn_msg.data.waiting_room.player[i].username);
        }
        // Backend::text = QString::fromStdString(conn_msg.data.waiting_room.player[0].username);
        emit waitingRoom();
    }
    else
    {
        emit refuse();
    }
    pthread_create(&tid, NULL, &pthread_waiting_room, NULL);
    // Wait for the thread to finish
    // pthread_join(tid, NULL);
    // emit gameStart();
}

void Backend::startGame()
{
    pthread_t tid;
    pthread_create(&tid, NULL, &pthread_game_state, NULL);
}

void Backend::updateWaitingRoom()
{
    textList.clear();
    for (int i = 0; i < conn_msg.data.waiting_room.joined; i++)
    {
        textList.append(conn_msg.data.waiting_room.player[i].username);
    }
    sleep(SLEEP_TIME);
    emit waitingRoom();
}

void Backend::updateGameState()
{
    textList.clear();
    textList.append(QString::fromStdString(conn_msg.data.game_state.crossword));
    for (int i = 0; i < PLAYER_PER_ROOM; i++)
    {
        textList.append(conn_msg.data.game_state.player[i].username);
        // textList.append(conn_msg.data.game_state.player[i].username);
        textList.append(QString::number(conn_msg.data.game_state.player[i].point));
        printf("Player %s has %d points\n", textList.at(1).toStdString().c_str(), textList.at(2).toInt());
    }
    // sleep(SLEEP_TIME);
    emit gameState();
}

void Backend::updateGameStateMyTurn()
{
    textList.clear();
    textList.append(QString::fromStdString(conn_msg.data.game_state.crossword));
    for (int i = 0; i < PLAYER_PER_ROOM; i++)
    {
        textList.append(conn_msg.data.game_state.player[i].username);
        // textList.append(conn_msg.data.game_state.player[i].username);
        textList.append(QString::number(conn_msg.data.game_state.player[i].point));
        printf("Player %s has %d points\n", textList.at(1).toStdString().c_str(), textList.at(2).toInt());
    }
    // sleep(SLEEP_TIME);
    emit gameStateMyTurn();
}

void Backend::updateNotification()
{
    textList.clear();
    textList.append(QString::fromStdString(conn_msg.data.notification));
    // sleep(SLEEP_TIME);
    emit notification();
}

void Backend::exitGame()
{
    exit(0);
}

void *pthread_waiting_room(void *arg)
{
    free(arg);
    pthread_detach(pthread_self());
    while (conn_msg.data.waiting_room.joined != PLAYER_PER_ROOM)
    {
        receive_server();
        // if(bytes_received <=0 ){
        //     printf("Server disconnected\n");
        //     emit Backend::instance->connectionFailed();
        //     pthread_cancel(pthread_self());
        // }

        if (conn_msg.type == WAITING_ROOM)
        {
            printf("New player joined\n");
            emit Backend::instance->userJoined();
        }
    }
    printf("All players joined\n");
    emit Backend::instance->gameStart();
    // emit Backend::instance->waitingRoom();
    pthread_cancel(pthread_self());
}

void *pthread_game_state(void *arg)
{
    free(arg);
    pthread_detach(pthread_self());
    while (conn_msg.type != END_GAME)
    {
        sleep(5);
        receive_server();
        if (bytes_received <= 0)
        {
            emit Backend::instance->connectionFailed();
            pthread_cancel(pthread_self());
        }
        if (conn_msg.type == GAME_STATE)
        {
            printf("Game state received\n");
            // If current player is my turn
            if (strcmp(conn_msg.data.game_state.player[conn_msg.data.game_state.turn].username, username) == 0)
            {
                printf("It's my turn\n");
                emit Backend::instance->updateGameStateSignalMyTurn();
            }
            else
            {
                emit Backend::instance->updateGameStateSignal();
            }
        }
        else if (conn_msg.type == NOTIFICATION)
        {
            printf("Notification received: %s\n", conn_msg.data.notification);
            emit Backend::instance->updateNotificationSignal();
            // sleep(SLEEP_TIME);
        }
    }
    pthread_cancel(pthread_self());
}
// pthread_mutex_destroy(&lock);


QStringList Backend::getTextList() const
{
    return textList;
}
