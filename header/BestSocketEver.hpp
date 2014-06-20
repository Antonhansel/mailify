#ifndef BEST_SOCKET_EVER_HPP
#define BEST_SOCKET_EVER_HPP

# include <QWidget>
# include <QtWidgets/QGridLayout>
# include <QTextEdit>
# include <QtNetwork>
# include <QSslSocket>
# include <QtCore>
# include <iostream>
# include <QLineEdit>

class BestSocketEver;

class BestSocketEverMonitor : public QWidget {
Q_OBJECT
public:
    BestSocketEverMonitor();
    void bindSocket(BestSocketEver *);
    QTextEdit       *_consoleText;
public slots:
    void    getInput();
private:
    BestSocketEver  *_socket;
    QWidget         *_window;
    QGridLayout     *_mainLayout;
    QLineEdit       *_lineedit;
};

class BestSocketEver : public QSslSocket {
Q_OBJECT
public:
    BestSocketEver();
    void    sendData(QString input);
    qint64  write(const QByteArray &byteArray);
    QByteArray      readAll();
// public slots:
//     void    _ready();
//     void    readTcpData();
private:
    int             _port;
    bool            _connected;
    std::function<void (std::string)>       _callback;
    BestSocketEverMonitor *_monitor;
};

#endif // BEST_SOCKET_EVER_HPP
