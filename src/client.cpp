#include "client.h"

Client::Client(string name) : BlumEntity(name) {
  _socket.connect(
      tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
}

void Client::set_keys() {
  long len = 150;
  while (p % 4 != 3) {
    GenPrime(p, len);
  }
  while ((q % 4 != 3) || (p == q)) {
    GenPrime(q, len);
  }
  n = p * q;
  do {
    RandomBnd(x, n);
  } while (GCD(x, n) != 1);
  x0 = SqrMod(x, n);
  x1 = SqrMod(x0, n);
}
void Client::protocol() {
  greet();
  receive_and_echo();
  set_keys();
  // speak(write_secrets());
  send_blum_integer_and_fourth_power();
  receive_guess();
  send_keys();
  set_head_or_tail();
  speak(write_head_or_tail());
  receive_head_or_tail();
  declare_head_or_tail();
}

int main() {
  Client bob("Bob");
  bob.protocol();
  return 0;
}
