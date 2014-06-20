#include "SendMail.hpp"
#include "MainUI.hpp"

SendMail::SendMail(MainUI *parent)
{
  _parent = parent;
  this->_window = new QWidget;
  this->_window->setFixedSize(1000, 1000);
  this->_window->setWindowTitle(tr("Send a new mail"));
  this->_window->show();
  this->_mainLayout = new QGridLayout;
  initInputs();
  this->_mainLayout->addWidget(_from, 0, 1);
  this->_mainLayout->addWidget(_fromLabel, 0, 0);
  this->_mainLayout->addWidget(_to, 1, 1);
  this->_mainLayout->addWidget(_toLabel, 1, 0);
  this->_mainLayout->addWidget(_subjectLabel, 2, 0);
  this->_mainLayout->addWidget(_subject, 2, 1);
  this->_mainLayout->addWidget(_text, 3, 1);
  this->_mainLayout->addWidget(_send, 4, 0);
  this->_window->setLayout(this->_mainLayout);
  QObject::connect(_send, SIGNAL(clicked()), this,SLOT(sendMessage(void)));
}

void  SendMail::sendMessage()
{
  QString input;

  _smtp = _parent->smtp();
  input = "<";
  input += _from->text();
  input += ">";
  _smtp->setFrom(input);
  input = "<";
  input += _to->text();
  input += ">";
  _smtp->setTo(input);
  input = "Subject: ";
  input += _subject->text();
  _smtp->setSubject(input);
  _smtp->setData(_text->toPlainText());
}

void SendMail::initInputs()
{
  _send = new QPushButton(this);
  _send->setText("Send message");
  _from = new QLineEdit(this);
  _from->setText(_parent->smtp()->username());
  _fromLabel = new QLabel(this);
  _fromLabel->setText("From: ");
  _fromLabel->setFixedWidth(130);
  _toLabel = new QLabel(this);
  _toLabel->setText("To:");
  _subjectLabel = new QLabel(this);
  _subjectLabel->setText("Subject: ");
  _to = new QLineEdit(this);
  _subject = new QLineEdit(this);
  _text = new QTextEdit(this);
  _text->setFrameStyle(QFrame::Box | QFrame::Sunken);
  _text->setReadOnly(false);
  _text->setStyleSheet("color: green ; background-color: black");
}

SendMail::~SendMail()
{

}
