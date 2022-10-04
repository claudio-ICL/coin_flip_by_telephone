#include "blum.h"

BlumEntity::BlumEntity(string name) : Entity(name) {}
void BlumEntity::receive_blum_integer_and_fourth_power() {
  receive({&n, &x1});
  _guess = RandomBnd(n) % 2;
}

ErrorCode BlumEntity::send_blum_integer_and_fourth_power() {
  return send({n, x1});
}
void BlumEntity::receive_keys() {
  receive({&p, &q, &x});
  x0 = SqrMod(x, n);
  x1 = SqrMod(x0, n);
}

ErrorCode BlumEntity::declare_head_or_tail() { return send(_head_or_tail); }

void BlumEntity::test() {
  assert(p % 4 == 3);
  assert(q % 4 == 3);
  assert(n == p * q);
  assert(SqrMod(x, n) == x0);
  assert(SqrMod(x0, n) == x1);
}

void BlumEntity::set_head_or_tail() {
  if (x % 2 == _guess)
    _head_or_tail = "head";
  else
    _head_or_tail = "tail";
}
string BlumEntity::write_secrets() {
  std::stringstream ss;
  ss << "\nSecret keys as held by " << _name << ":" << std::endl;
  ss << "p: " << p << std::endl;
  ss << "q: " << q << std::endl;
  ss << "x: " << x << std::endl;
  return ss.str();
}
string BlumEntity::write_blum_integer_and_forth_power() {
  std::stringstream ss;
  ss << "\nPublic keys as held by " << _name << ":" << std::endl;
  ss << "n: " << n << std::endl;
  ss << "x1: " << x1 << std::endl;
  return ss.str();
}
string BlumEntity::write_head_or_tail() {
  std::stringstream ss;
  ss << "\nCoin flip as held by " << _name << ": ";
  ss << _head_or_tail << std::endl;
  return ss.str();
}

void BlumEntity::receive_head_or_tail() {
  string msg = receive();
  int t = (msg.compare(_head_or_tail) == 0);
  assert(t == 0);
}
