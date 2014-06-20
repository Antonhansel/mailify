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

void  Smtp::sendData(QString input)
{
    _pSocket.sendData(input);
}

void Smtp::initSmtp()
{
    connect(&_pSocket, SIGNAL(readyRead()), SLOT(readTcpData()));
    _pSocket.connectToHost(_server, _port);
    _pSocket.waitForConnected();
}

bool Smtp::isConnected() const
{
  return (_connected);
}

void  Smtp::setFrom(QString from)
{
  QString tmp;

  _from = from;
  tmp = "MAIL FROM: ";
  tmp += _from;
  printf("From : %s\n", tmp.toUtf8().data());
  sendData(tmp);
}

void Smtp::setTo(QString to)
{
  _to = to;
}

void  Smtp::setData(QString data)
{
  _data = data;
}

void  Smtp::setSubject(QString subject)
{
  _subject = subject;
}

void Smtp::readTcpData()
{
  QString input;
  QByteArray   	data = _pSocket.readAll();
  if (_connected == true)
  {
    if (data.startsWith("250 2.1") || data.startsWith("354"))
    {
        if (_step == 6)
        {
          input = "RCPT TO: ";
          input += _to;
          sendData(input);
          _step++;
        }
        else if (_step == 7)
        {
          sendData("DATA");
          _step++;
        }
        else if (_step == 8)
        {
          input = "From: ";
          input += _to;
          sendData(input);
          input = "To: ";
          input += _to;
          sendData(input);
          sendData(_subject);
          sendData(_data);
          sendData("\r\n.\r");
          _step = 6;
        }
    }
   }
  else if (_step == -1 && data.startsWith("220"))
  {
    sendData("EHLO localhost");
    _step++;
  }
  else if (_step == 0 && data.startsWith("250"))
  {
    sendData("STARTTLS");
    _step++;
  }
  else if (_step == 1 && data.startsWith("220 2.0.0 Ready to start TLS"))
  {
    _pSocket.startClientEncryption();
    usleep(300);
    sendData("EHLO google.fr");
    _step++;
  }
  else if (_step == 2)
  {
    sendData("AUTH LOGIN");
    _step++;
  }
  else if (_step == 3 && data.startsWith("334"))
  {
    if (_username.endsWith("@gmail.com"))
        sendData(_username.toUtf8().toBase64());
    else
        sendData(_username);
   _step++;
  }
  else if (_step == 4 && data.startsWith("334"))
  {
    if (_username.endsWith("@gmail.com"))
        sendData(_password.toUtf8().toBase64());
    else
        sendData(_password);
    _step++;
  }
  else if (_step == 5 && data.startsWith("235"))
  {
    _callback("");
    _step++;
    _connected = true;
  }
  else if (_step == 5 && data.startsWith("535"))
  {
    _callback("Error with login");
  }
}

QString &Smtp::username()
{
  return _username;
}

