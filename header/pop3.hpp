#ifndef POP3_HPP
#define POP3_HPP

#include "AMailRetrieve.hpp"

class pop3 : public AMailRetrieve {
public:
    pop3();
    ~pop3();
    bool connect(QString &user, QString &pass, QString &server, int port);
    std::vector<AMail *> &getMails();
};

#endif // POP3_HPP
