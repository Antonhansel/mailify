#ifndef IMAP_HPP
#define IMAP_HPP

#include "BestSocketEver.hpp"
#include "AMailRetrieve.hpp"

class Imap : public AMailRetrieve {
public:
    Imap();
    ~Imap();
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

class ImapMail : public AMail {
public:
    ~ImapMail() {};
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

#endif // IMAP_HPP
