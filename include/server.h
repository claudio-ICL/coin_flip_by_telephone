#ifndef SERVER_H
#define SERVER_H

#include "blum.h"

class Server : BlumEntity {
public:
  Server(string);
  void protocol();

private:
  tcp::acceptor _acceptor;
};
#endif // SERVER_H
