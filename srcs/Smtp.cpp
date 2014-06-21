#include "Smtp.hpp"
#include "Connexion.hpp"

Smtp::Smtp()
{
}

void Smtp::initConnexion(QString &username, QString &password, QString &server, int port, std::function<void (std::string)> callback)
{
    _username = username;
    _password = password;
    _server = server;
    _port = port;
    _callback = callback;
    _step = -1;
    initSmtp();
}

void Smtp::initSmtp()
{
    _pSocket.addNextCallback([this] (QByteArray data) {
      if (!data.startsWith("220"))
      {
        _pSocket.clearCallbacks();
        return _callback("Server is not a SMTP server");
      }
      _pSocket.sendData("HELO localhost");
    });
    _pSocket.addNextCallback([this] (QByteArray data) {
      if (!data.startsWith("250"))
      {
        _pSocket.clearCallbacks();
        return _callback("Server is not a SMTP server");
      }
      _pSocket.sendData("STARTTLS");
    });
    _pSocket.addNextCallback([this] (QByteArray data) {
      if (!data.startsWith("220 2.0.0 Ready to start TLS"))
      {
        _pSocket.clearCallbacks();
        return _callback("Server doesn't support TLS");
      }
      _pSocket.startClientEncryption();
      usleep(300);
      _pSocket.sendData("HELO google.fr");
    });
    _pSocket.addNextCallback([this] (QByteArray) {
      _pSocket.sendData("AUTH LOGIN");
    });
    _pSocket.addNextCallback([this] (QByteArray data) {
      if (!data.startsWith("334"))
      {
        _pSocket.clearCallbacks();
        return _callback("Server doesn't support login");
      }
      if (_username.endsWith("@gmail.com"))
          _pSocket.sendData(_username.toUtf8().toBase64());
      else
          _pSocket.sendData(_username);
    });
    _pSocket.addNextCallback([this] (QByteArray data) {
      if (!data.startsWith("334"))
      {
        _pSocket.clearCallbacks();
        return _callback("Wrong login");
      }
      if (_username.endsWith("@gmail.com"))
          _pSocket.sendData(_password.toUtf8().toBase64());
      else
          _pSocket.sendData(_password);
    });
    _pSocket.addNextCallback([this] (QByteArray data) {
      if (!data.startsWith("235"))
      {
        _pSocket.clearCallbacks();
        return _callback("Wrong login or password");
      }
      return _callback("");
    });
    _pSocket.connectToHost(_server, _port);
    _pSocket.waitForConnected();
}

bool Smtp::isConnected() const
{
  return (_connected);
}

void Smtp::sendMail(QString from, QString to, QString subject, QString data, std::function<void (std::string)> callback)
{
    _pSocket.addNextCallback([this, to, callback] (QByteArray data) {
      if (!data.startsWith("250 2.1"))
      {
        _pSocket.clearCallbacks();
        return callback("Error while sending mail at MAIL FROM");
      }
      _pSocket.sendData("RCPT TO: <" + to + ">");
    });
    _pSocket.addNextCallback([this, callback] (QByteArray data) {
      if (!data.startsWith("250 2.1"))
      {
        _pSocket.clearCallbacks();
        return callback("Error at RCPT TO");
      }
      _pSocket.sendData("DATA");
    });
    _pSocket.addNextCallback([this, from, to, subject, data] (QByteArray) {
      _pSocket.sendData("From: <" + from + ">");
      _pSocket.sendData("To: <" + to + ">");
      _pSocket.sendData("Subject: " + subject);
      _pSocket.sendData(data);
      _pSocket.sendData("\r\n.\r");
    });
    _pSocket.addNextCallback([callback, this] (QByteArray data) {
      if (!data.startsWith("250"))
      {
        _pSocket.clearCallbacks();
        return callback("Error at end of DATA");
      }
      return callback("");
    });
    _pSocket.sendData("MAIL FROM: <" + from + ">");
}

QString &Smtp::username()
{
  return _username;
}

