#ifndef CLIENT_H
#define CLIENT_H
#include "blum.h"

class Client : BlumEntity {
public:
  Client(string);
  void set_keys();
  void protocol();
};
#endif // CLIENT_H
