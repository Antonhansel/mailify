#include "Imap.hpp"
#include <regex>

Imap::Imap() {};
Imap::~Imap() {
    // Close connection
};

void Imap::initConnexion(QString &user, QString &pass, QString &server, int port, std::function<void (std::string)> callback)
{
    _server = server;
    _port = port;
    _user = user;
    _pass = pass;
    _socket.addNextCallback([this, callback] (QByteArray data) {
        if (!data.startsWith("* OK Gimap ready for requests"))
        {
            _socket.clearCallbacks();
            return callback("Server is not a Imap server");
        }
        _socket.sendData("tag login " + _user + " " +_pass + "\r");
    });
    _socket.addNextCallback([this, callback] (QByteArray data) {
        if (!data.startsWith("*"))
        {
            _socket.clearCallbacks();
            return callback("Can't login");
        }
    _socket.sendData("tag SELECT \"inbox\"\r");
    });
    _socket.addNextCallback([this, callback] (QByteArray data) {
        if (!data.startsWith("*"))
        {
            _socket.clearCallbacks();
            return callback("Cant get unseen mail number");
        }
        parsMailNumber(data);
        callback("");
    });
    _socket.connectToHost(_server, _port);
    _socket.waitForConnected();
    _socket.startClientEncryption();
}

void    Imap::parsMailNumber(QByteArray data)
{
    int tmpend, tmp;
    QString temp;
    tmpend = data.indexOf("EXISTS");
    tmp = tmpend - 10;
    temp = data.mid(tmp, data.size() - tmp).data();
    data = temp.toUtf8();
    tmp = data.indexOf("*");
    temp = data.mid(tmp - 1, data.indexOf("EXISTS", tmp) - tmp).data();
    temp = temp.remove(0, 3);
    _number = temp.toInt();
}

void Imap::getFolders(std::function<void (std::string)> callback)
{
    _socket.sendData("tag list \"\" \"*\"\r");
    _socket.addNextCallback([this, callback] (QByteArray data) {
        if (!data.startsWith("* LIST"))
        {
            _socket.clearCallbacks();
            return callback("Cant list folders");
        }
    callback("");
    });
}

void Imap::getMails(std::function<void (std::vector<AMail *>)> callback)
{
    for(unsigned i = 2; i < 15; ++i) {
    _socket.addNextCallback([this, i, callback] (QByteArray data) {
        ImapMail *mail = new ImapMail();
        mail->parseFromData(data);
        _mails.push_back(mail);
        if (i == 14)
        {
            callback(_mails);
            return;
        }
        char tmp[30];
        QString input;
        snprintf(tmp, 29, "%d", _number - i);
        _socket.sendData("tag FETCH " + QString(tmp) + " body[]\r");
        std::cout << data.data() << std::endl;
    }, [] (QByteArray data) {return data.endsWith("tag OK Success\r\n");});
    }
    _socket.sendData("tag FETCH 1 body[]\r");
}

void ImapMail::parseFromData(QByteArray &data)
{
    int tmp;

    tmp = data.indexOf("From: ");
    _sender = QString::fromUtf8(data.mid(tmp + 6, data.indexOf("\n", tmp) - tmp - 6).data());
    tmp = data.indexOf("Subject: ");
    _subject = QString::fromUtf8(data.mid(tmp + 9, data.indexOf("\n", tmp) - tmp - 9).data());
    _parseBoundary(data, true);
}

void ImapMail::_parseBoundary(QByteArray &data, bool ignoreNoBoundary)
{
    int tmp;
    QString boundary;

    if ((tmp = data.indexOf("boundary=\"")) != -1)
    {
        QStringList parts;
        boundary = "--" + data.mid(tmp + 10, data.indexOf("\"", tmp + 10) - tmp - 10);
        parts = QString::fromUtf8(data.data()).split(boundary + "\r\n");
        tmp = data.indexOf(boundary, tmp + boundary.length()) + boundary.length();
        for (int i = 1; i < parts.size(); ++i)
        {
            if (parts.at(i).contains("boundary=\""))
            {
                QByteArray tmp = parts.at(i).toUtf8();
                return _parseBoundary(tmp, false);
            }
            else if (parts.at(i).contains("Content-Type: text/html;"))
            {
                tmp = parts.at(i).indexOf("\r\n\r\n");
                _content = parts.at(i).mid(tmp + 2, parts.at(i).length() - tmp - boundary.length() - 10);
            }
        }
    }
    else if (ignoreNoBoundary)
    {
        tmp = data.indexOf("\r\n\r\n");
        _content = QString::fromUtf8(data.mid(tmp + 4, data.size() - tmp - 24).data());
        _content.replace("\n", "<br/>");
    }
}

QString &ImapMail::subject()
{
    return _subject;
}

QString &ImapMail::sender()
{
    return _sender;
}

QString &ImapMail::content()
{
    return _content;
}

void ImapMail::remove(std::function<void (std::string)> callback)
{
    callback("");
}

void Imap::getStatus(std::function<void (std::string)> callback)
{
    // _socket.sendData("tag status inbox (messages)\r");
    // _socket.addNextCallback([this, callback] (QByteArray data) {
    //     if (!data.startsWith("* STATUS"))
    //     {
    //         _socket.clearCallbacks();
    //         return callback("Cant list mails");
    //     }
    //     _socket.sendData("tag status inbox (unseen)\r");
    // });
    // _socket.addNextCallback([this, callback] (QByteArray data) {
    //     if (!data.startsWith("* STATUS"))
    //     {
    //         _socket.clearCallbacks();
    //         return callback("Cant get unseen mail number");
    //     }
    //     _socket.sendData("tag SELECT \"inbox\"\r");
    // });
    // _socket.addNextCallback([this, callback] (QByteArray data) {
    //     if (!data.startsWith("*"))
    //     {
    //         _socket.clearCallbacks();
    //         return callback("Cant get unseen mail number");
    //     }
    //     callback("");
    // });
}
