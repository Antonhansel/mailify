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
# include <QString>
# include <QMutex>
# include <queue>
# include <QMutexLocker>

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
    void            addNextCallback(std::function<void (QByteArray)>, std::function<bool (QByteArray)> = [] (QByteArray data) {return data.endsWith("\n");});
    void            clearCallbacks();
    void            connectToHost(const QString &, quint16, QIODevice::OpenMode openMode = ReadWrite);
private slots:
    void            _receiving();
private:
    QMutex          _sendMutex;
    QMutex          _receiveMutex;
    int             _port;
    bool            _connected;
    std::queue<std::pair<std::function<void (QByteArray)>, std::function<bool (QByteArray)>>>       _callbacks;
    BestSocketEverMonitor *_monitor;
};

#endif // BEST_SOCKET_EVER_HPP
