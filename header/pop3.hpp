#ifndef POP3_HPP
#define POP3_HPP

#include "AMailRetrieve.hpp"

class pop3 : public AMailRetrieve {
public:
    pop3();
    ~pop3();
    void connect(QString &user, QString &pass, QString &server, int port, std::function<void (std::string)>);
    void getMails(std::function<void (std::vector<AMail *>)>);
private:
    std::function<void (std::string)>   _callback;
};

#endif // POP3_HPP
