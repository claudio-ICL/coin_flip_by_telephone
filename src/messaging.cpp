#include "messaging.h"

string messaging::receive(tcp::socket &socket) {
  boost::asio::streambuf buf;
  string data;
  boost::system::error_code error;
  boost::asio::read_until(socket, buf, "\n", error);
  if (error && error != boost::asio::error::eof) {
    std::cout << "receive failed: " << error.message() << std::endl;
  } else {
    data = boost::asio::buffer_cast<const char *>(buf.data());
  }
  return data;
}
boost::system::error_code messaging::send(tcp::socket &socket,
                                          const string &message) {
  string msg = message + "\n";
  boost::system::error_code error;
  boost::asio::write(socket, boost::asio::buffer(msg), error);
  return error;
}

Entity::Entity(const string &name)
    : _ioservice(), _socket(_ioservice), _name(name){};

string Entity::receive() { return messaging::receive(_socket); }
ErrorCode Entity::send(const string &msg) {
  return messaging::send(_socket, msg);
}

ErrorCode Entity::greet() {
  std::stringstream ss;
  ss << "Hello from " << _name << "!";
  return speak_and_send(ss.str());
}

void Entity::speak(const string &msg) {
  std::cout << std::left << std::setw(60) << msg << std::endl;
}

void Entity::echo(const string &msg) {
  std::cout << std::right << std::setw(60) << msg << std::endl;
}

ErrorCode Entity::speak_and_send(const string &msg) {
  speak(msg);
  return send(msg);
}
string Entity::receive_and_echo() {
  string msg = receive();
  echo(msg);
  return msg;
}

ErrorCode Entity::send(bool b) {
  string msg = (b) ? "1" : "0";
  return send(msg);
}

ErrorCode Entity::send(std::initializer_list<ZZ> args) {
  std::stringstream ss;
  for (auto arg : args) {
    ss << arg << " ";
  }
  return send(ss.str());
}

void Entity::receive(bool &b) {
  string msg = receive();
  std::stringstream ss;
  ss << msg;
  ss >> b;
}

void Entity::receive(std::initializer_list<ZZ *> args) {
  string msg = receive();
  std::stringstream ss;
  ss << msg;
  for (ZZ *arg : args) {
    ss >> *arg;
  }
}
