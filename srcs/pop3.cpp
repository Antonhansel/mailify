#include "pop3.hpp"
#include <regex>

pop3::pop3() {};
pop3::~pop3() {
    // Close connection
};

void pop3::getFolders(std::function<void (std::string)> callback)
{
    return ;
}

void pop3::initConnexion(QString &user, QString &pass, QString &server, int port, std::function<void (std::string)> callback)
{
    _server = server;
    _port = port;
    _user = user;
    _pass = pass;
    _socket.addNextCallback([this, callback] (QByteArray data) {
        if (!data.startsWith("+OK"))
        {
            _socket.clearCallbacks();
            return callback("Server is not a POP3 server");
        }
        _socket.sendData("USER " + _user);
    });
    _socket.addNextCallback([this, callback] (QByteArray data) {
        if (!data.startsWith("+OK"))
        {
            _socket.clearCallbacks();
            return callback("Wrong Username");
        }
        _socket.sendData("PASS " + _pass);
    });
    _socket.addNextCallback([this, callback] (QByteArray data) {
        if (!data.startsWith("+OK"))
        {
            _socket.clearCallbacks();
            return callback("Wrong Password");
        }
        callback("");
    });
    _socket.connectToHost(_server, _port);
    _socket.waitForConnected();
    _socket.startClientEncryption();
}

void pop3::getMails(std::function<void (std::vector<AMail *>)> callback)
{
    for(unsigned i = 2; i < 15; ++i) {
        _socket.addNextCallback([this, i, callback] (QByteArray data) {
            pop3Mail *mail = new pop3Mail();
            mail->parseFromData(data);
            _mails.push_back(mail);
            if (i == 14)
            {
                callback(_mails);
                return;
            }
            char tmp[30];
            QString input;
            snprintf(tmp, 29, "%d", i);
            input = "RETR ";
            input += tmp;
            _socket.sendData(input);
        }, [] (QByteArray data) {return data.endsWith(".\r\n");});
    }
    _socket.sendData("RETR 1");
}

QString &pop3Mail::subject()
{
    return _subject;
}

QString &pop3Mail::sender()
{
    return _sender;
}

QString &pop3Mail::content()
{
    return _content;
}

void pop3Mail::remove(std::function<void (std::string)> callback)
{
    callback("");
}

void pop3Mail::parseFromData(QByteArray &data)
{
    int tmp;

    tmp = data.indexOf("Subject: ");
    _subject = data.mid(tmp + 9, data.indexOf("\n", tmp) - tmp - 9).data();
    tmp = data.indexOf("To: ");
    _sender = data.mid(tmp + 4, data.indexOf("\n", tmp) - tmp - 4).data();
    tmp = data.indexOf("\r\n\r\n");
    _content = data.mid(tmp + 4, data.size() - tmp - 9).data();
}

