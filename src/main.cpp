#include "TorrentParser.h"
#include <iostream>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

using namespace std;

namespace asio = boost::asio;
// g++ -I /usr/include/boost -L /usr/lib/x86_64-linux-gnu -lboost_system -lboost_thread  main.cpp TorrentParser.cpp -o torrent -std=c++17 -pthread
int main() {
    TorrentParser tp("/home/songguan/torrent/debian.torrent");
    cout << tp.getInfoHash() << endl;
    //std::cout << tp.getLength() << std::endl;
    // auto vec = tp.getPieces();
    // for (auto& p : vec) {
    //     std::cout << p << std::endl;
    // }

    // asio::io_context io_context;
    // boost::system::error_code ec;
    // asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);
    // asio::ip::tcp::socket socket(io_context);

    // socket.connect(endpoint, ec);
    // if (!ec) {
    //     cout << "Connected" << endl;
    // } else {
    //     cout << "Failed" << endl;
    // }

}