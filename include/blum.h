#ifndef BLUM_H
#define BLUM_H

#include "messaging.h"
#include <NTL/ZZ.h>
#include <boost/asio.hpp>
#include <iostream>

using namespace NTL;
using namespace boost::asio;
using ip::tcp;

class BlumEntity : protected Entity {
public:
  BlumEntity(string);
  void receive_blum_integer_and_fourth_power();
  ErrorCode send_blum_integer_and_fourth_power();
  ErrorCode send_guess() { return send(_guess); }
  void receive_guess() { receive(_guess); }
  void receive_keys();
  ErrorCode send_keys() { return send({p, q, x}); }
  ErrorCode declare_head_or_tail();
  void receive_head_or_tail();
  string write_secrets();
  string write_blum_integer_and_forth_power();
  string write_head_or_tail();

protected:
  ZZ x;  // 1<x<n suche that gcd(x,n) = 1
  ZZ x0; // square of x
  ZZ x1; // suqare of x0
  ZZ n;  // Blum integer
  ZZ p;  // first factor of n
  ZZ q;  // second factor of n
  void test();
  void set_head_or_tail();
  bool _guess;
  string _head_or_tail;
};
#endif // BLUM_H
