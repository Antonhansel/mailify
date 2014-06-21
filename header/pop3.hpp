#ifndef POP3_HPP
#define POP3_HPP

#include "BestSocketEver.hpp"
#include "AMailRetrieve.hpp"

class pop3 : public AMailRetrieve {
public:
    pop3();
    ~pop3();
    void initConnexion(QString &user, QString &pass, QString &server, int port, std::function<void (std::string)>);
    void getMails(std::function<void (std::vector<AMail *>)>);
private slots:
    void _readTcpData();
private:
    std::function<void (std::string)>   _callback;
    BestSocketEver                      _socket;
    QString                             _server;
    QString                             _user;
    QString                             _pass;
    int                                 _port;
    std::vector<AMail *>                _mails;
};

class pop3Mail : public AMail {
public:
    ~pop3Mail() {};
    QString &subject();
    QString &sender();
    QString &content();
    void remove(std::function<void (std::string)>);
    void parseFromData(QByteArray &);
private:
    QString     _subject;
    QString     _sender;
    QString     _content;
};

#endif // POP3_HPP
