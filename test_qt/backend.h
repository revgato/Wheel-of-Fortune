#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class Backend: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

public:
    explicit Backend(QObject *parent = nullptr):QObject(parent){

    }
    Q_INVOKABLE void login(QString const &username, QString const &password){
        if(username == "youtube" && password == "youtube"){
            emit loginSuccess();
        }else{
            setStatus("Username/Password in correct");
            emit loginFail();
        }
    };
    QString status()const{
        return mStatus;
    };
    void setStatus(QString const &status){
        if(mStatus == status){
            return;
        }
        mStatus = status;
        emit statusChanged();
    };

signals:
    void loginSuccess();
    void loginFail();
    void statusChanged();
private:
    QString mStatus;
};
#endif // BACKEND_H
