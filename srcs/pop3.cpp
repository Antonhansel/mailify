#include "pop3.hpp"

pop3::pop3() {};
pop3::~pop3() {
    // Close connection
};

void pop3::connect(QString &user, QString &pass, QString &server, int port, std::function<void (std::string)> callback)
{

}

void pop3::getMails(std::function<void (std::vector<AMail *>)>)
{

}
