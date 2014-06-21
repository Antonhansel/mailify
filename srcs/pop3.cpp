#include "pop3.hpp"

pop3::pop3() {};
pop3::~pop3() {
    // Close connection
};

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
    connect(&_socket, SIGNAL(readyRead()), SLOT(_readTcpData()));
    _socket.connectToHost(_server, _port);
    _socket.waitForConnected();
    _socket.startClientEncryption();
}

void pop3::getMails(std::function<void (std::vector<AMail *>)>)
{

}

void pop3::_readTcpData()
{

}
