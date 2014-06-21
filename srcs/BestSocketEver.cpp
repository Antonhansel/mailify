#include "BestSocketEver.hpp"

BestSocketEver::BestSocketEver()
{
    _connected = false;
    _monitor = new BestSocketEverMonitor;
    connect(this, SIGNAL(readyRead()), SLOT(_receiving()));
}

void  BestSocketEver::sendData(QString input)
{
    input += '\n';
    write(input.toUtf8());
}

void BestSocketEver::connectToHost(const QString &address, quint16 port, QIODevice::OpenMode mode)
{
    _monitor->_consoleText->append("Connecting to : " + address);
    QSslSocket::connectToHost(address, port, mode);
}

qint64  BestSocketEver::write(const QByteArray &byteArray)
{
    QMutexLocker lock(&_sendMutex);
    _monitor->_consoleText->append(byteArray);
    return QSslSocket::write(byteArray);
}

QByteArray BestSocketEver::readAll()
{
    QByteArray tmp = QSslSocket::readAll();
    _monitor->_consoleText->append(tmp.data());
    return (tmp);
}

void       BestSocketEver::addNextCallback(std::function<void (QByteArray)> callback, std::function<bool (QByteArray)> waiterFunction)
{
    _callbacks.push(std::make_pair(callback, waiterFunction));
}

void        BestSocketEver::clearCallbacks()
{
    while (!_callbacks.empty())
        _callbacks.pop();
}

void       BestSocketEver::_receiving()
{
    static QByteArray buffer;
    QByteArray tmp;

    if (!_callbacks.size())
        return;
    QMutexLocker lock(&_receiveMutex);
    buffer.append(readAll());
    auto callback = _callbacks.front();
    if (callback.second(buffer))
    {
        tmp = buffer;
        buffer.clear();
        _callbacks.pop();
        return callback.first(tmp);
    }
}

BestSocketEverMonitor::BestSocketEverMonitor()
{
    _window = new QWidget;
    _window->show();
    _window->setFixedSize(1000, 1000);
    _window->setWindowTitle(tr("Debug Smtp"));
    _consoleText = new QTextEdit(this);
    _consoleText->setFrameStyle(QFrame::Box | QFrame::Sunken);
    _consoleText->setReadOnly(true);
    _consoleText->setStyleSheet("color: green ; background-color: black");
    _lineedit = new QLineEdit(this);
    _mainLayout = new QGridLayout;
    _mainLayout->addWidget(_consoleText, 0, 0);
    _mainLayout->addWidget(_lineedit, 1, 0);
    _window->setLayout(_mainLayout);
    QObject::connect(_lineedit, SIGNAL(returnPressed()),
        this, SLOT(getInput(void)));
}

void    BestSocketEverMonitor::bindSocket(BestSocketEver *socket)
{
    _socket = socket;
}

void  BestSocketEverMonitor::getInput()
{
    _lineedit->setText("");
    _socket->sendData(_lineedit->text());
}

