#include "server.h"

Server::Server(string name)
    : BlumEntity(name), _acceptor(_ioservice, tcp::endpoint(tcp::v4(), 1234)) {
  // wait for connection
  _acceptor.accept(_socket);
}

void Server::protocol() {
  receive_and_echo();
  greet();
  receive_blum_integer_and_fourth_power();
  speak(write_blum_integer_and_forth_power());
  send_guess();
  receive_keys();
  // speak(write_secrets());
  test();
  set_head_or_tail();
  speak(write_head_or_tail());
  declare_head_or_tail();
  receive_head_or_tail();
}

int main() {
  Server alice("Alice");
  alice.protocol();
  return 0;
}
