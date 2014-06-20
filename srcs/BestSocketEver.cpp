#include "BestSocketEver.hpp"

BestSocketEver::BestSocketEver()
{
    _connected = false;
    _monitor = new BestSocketEverMonitor;
}

void  BestSocketEver::sendData(QString input)
{
    _monitor->_consoleText->append(input);
    input += '\n';
    write(input.toUtf8());
}

qint64  BestSocketEver::write(const QByteArray &byteArray)
{
    _monitor->_consoleText->append(byteArray);
    return QSslSocket::write(byteArray);
}

QByteArray BestSocketEver::readAll()
{
    QByteArray tmp = QSslSocket::readAll();
    _monitor->_consoleText->append(tmp.data());
    return (tmp);
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

