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
    void getFolders(std::function<void (std::vector<std::string>)>);
    void parsFolders(QByteArray data);
    void switchFolder(std::string folder);
private slots:
    void    _readTcpData();
private:
    std::function<void (std::string)>   _callback;
    BestSocketEver                      _socket;
    QString                             _server;
    QString                             _user;
    QString                             _pass;
    int                                 _port;
    std::vector<AMail *>                _mails;
    std::vector<std::string>            _folders;
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
