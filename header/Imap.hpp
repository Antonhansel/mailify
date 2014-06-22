#ifndef IMAP_HPP
#define IMAP_HPP

#include "BestSocketEver.hpp"
#include "AMailRetrieve.hpp"

class Imap : public AMailRetrieve {
public:
    Imap();
    ~Imap();
    void parsMailNumber(QByteArray data);
    void initConnexion(QString &user, QString &pass, QString &server, int port, std::function<void (std::string)>);
    void getMails(std::function<void (std::vector<AMail *>)>);
private slots:
    void    _readTcpData();
    void    getFolders(std::function<void (std::string)> callback);
    void    getStatus(std::function<void (std::string)> callback);
private:
    std::function<void (std::string)>   _callback;
    BestSocketEver                      _socket;
    QString                             _server;
    QString                             _user;
    QString                             _pass;
    int                                 _port;
    std::vector<AMail *>                _mails;
    int                                 _number;
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
    void    _parseBoundary(QByteArray &, bool);
    QString     _subject;
    QString     _sender;
    QString     _content;
};

#endif // IMAP_HPP
