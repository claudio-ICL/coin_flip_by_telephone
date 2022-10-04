#ifndef MESSAGING_H
#define MESSAGING_H
#include <NTL/ZZ.h>
#include <boost/asio.hpp>
#include <iomanip>
#include <iostream>
using namespace boost::asio;
using namespace NTL;
using ip::tcp;
using std::string;
typedef boost::system::error_code ErrorCode;

namespace messaging {
string receive(tcp::socket &socket);
boost::system::error_code send(tcp::socket &socket, const string &message);
} // namespace messaging

class Entity {
public:
  Entity(const string &);
  ErrorCode send(const string &);
  ErrorCode send(bool);
  ErrorCode send(std::initializer_list<ZZ>);
  string receive();
  void receive(bool &);
  void receive(std::initializer_list<ZZ *>);
  ErrorCode greet();
  void speak(const string &);
  void echo(const string &);
  ErrorCode speak_and_send(const string &);
  string receive_and_echo();

protected:
  boost::asio::io_service _ioservice;
  tcp::socket _socket;
  string _name;
};

#endif // MESSAGING_H
