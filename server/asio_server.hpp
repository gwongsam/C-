#pragma once
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using namespace boost::asio;

void asio_server() {
  // https://www.cnblogs.com/fnlingnzb-learner/p/10411558.html
  io_service iosev;
  ip::tcp::acceptor acceptor(iosev, ip::tcp::endpoint(ip::tcp::v4(), 1000));
  while (true) {
    ip::tcp::socket socket(iosev);
    acceptor.accept(socket);
    std::cout << socket.remote_endpoint().address() << endl;
    boost::array<char, 128> buf;
    boost::system::error_code ec;
    socket.read_some(boost::asio::buffer(buf));
    socket.write_some(buffer("hello world!"), ec);
    cout << buf.data() << endl;

    if (ec) {
      cout << boost::system::system_error(ec).what() << endl;
      break;
    }
  }
}
