#include "Connexion.hpp"
#include "MainUI.hpp"
#include "pop3.hpp"

void	Connexion::applyLayouts()
{
    _mainLayout->addWidget(_addressLabel, 0, 0);
    _mainLayout->addWidget(_address, 0, 1);
    _mainLayout->addWidget(_passLabel, 1, 0);
    _mainLayout->addWidget(_pass, 1, 1);
    _mainLayout->addWidget(_serverAddressLabel, 2, 0);
    _mainLayout->addWidget(_serverAddress, 2, 1);
    _mainLayout->addWidget(_portLabel, 3, 0);
    _mainLayout->addWidget(_port, 3, 1);
    _mainLayout->addWidget(_receiveServerAddressLabel, 4, 0);
    _mainLayout->addWidget(_receiveServerAddress, 4, 1);
    _mainLayout->addWidget(_receivePortLabel, 5, 0);
    _mainLayout->addWidget(_receivePort, 5, 1);
    _mainLayout->addWidget(_errorLabel, 6, 0);
    _mainLayout->addWidget(_connect, 6, 1);
}

void Connexion::connectSlots()
{
    QObject::connect(_connect, SIGNAL(clicked()), this,SLOT(tryConnect(void)));
}

void  Connexion::tryConnect()
{
    _addressString = _address->text();
    _passString = _pass->text();
    _serverAddressString = _serverAddress->text();
    _portString = _port->text();
    _receiveServerAddressString = _receiveServerAddress->text();
    _receivePortString = _receivePort->text();
    if (!_addressString.size() || !_passString.size()
        || !_serverAddressString.size() || !_portString.size()
        || !_receiveServerAddressString.size() || !_receivePortString.size())
    {
        _errorLabel->setText("Fill every field");
        return;
    }
    _parent->smtp()->initConnexion(_addressString, _passString, _serverAddressString, atoi(_portString.toUtf8()), [this] (std::string error) {
        if (error.size())
        {
            _errorLabel->setText(error.c_str());
            return;
        }
        this->_window->hide();
    });
    auto pop = new pop3();
    pop->initConnexion(_addressString, _passString, _receiveServerAddressString, atoi(_receivePortString.toUtf8()), [] (std::string) {});
}

void  Connexion::initConnexionStuff()
{
    _address = new QLineEdit(this);
    _addressLabel = new QLabel(this);
    _addressLabel->setText("Address");
    _addressLabel->setFixedWidth(200);
    _pass = new QLineEdit(this);
    _pass->setEchoMode(QLineEdit::Password);
    _passLabel = new QLabel(this);
    _passLabel->setText("Password");
    _serverAddress = new QLineEdit(this);
    _serverAddress->setText("smtp.gmail.com");
    _serverAddressLabel = new QLabel(this);
    _serverAddressLabel->setText("Server Address");
    _port = new QLineEdit(this);
    _port->setText("587");
    _portLabel = new QLabel(this);
    _portLabel->setText("Server Port");
    _receiveServerAddress = new QLineEdit(this);
    _receiveServerAddress->setText("pop.gmail.com");
    _receiveServerAddressLabel = new QLabel(this);
    _receiveServerAddressLabel->setText("Receive Server Address");
    _receivePort = new QLineEdit(this);
    _receivePort->setText("995");
    _receivePortLabel = new QLabel(this);
    _receivePortLabel->setText("Server Port");
    _connect = new QPushButton(this);
    _connect->setText("Connect!");
    _errorLabel = new QLabel(this);
}

void	Connexion::initLayouts()
{
    initConnexionStuff();
}

void	Connexion::initUi()
{
    this->_mainLayout = new QGridLayout;
    this->_window->setFixedSize(500, 400);
    this->_window->setWindowTitle(tr("Connexion"));
    this->_window->setStyleSheet("color: #CFD6D7; background-color: #403075");
}

Connexion::Connexion(MainUI *parent) : QWidget()
{
    _parent = parent;
    _displayAll = true;
    _window = new QWidget;
    initUi();
    initLayouts();
    applyLayouts();
    connectSlots();
    this->_window->setLayout(this->_mainLayout);
    this->_window->show();
}

QString   Connexion::getUsername() const
{
    return (_addressString);
}

QString Connexion::getPassword() const
{
    return (_passString);
}
