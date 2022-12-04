#pragma once

#include <bencode.hpp>
#include <fstream>
#include <vector>
#include <iostream>

class TorrentParser {
private:

    std::string fileName;
    std::string infoHash;
    bencode::dict value;
    bencode::dict info;
    const int HASHLEN = 20;

public:

    TorrentParser(const std::string& _f);

    std::string getAnnounce() const;

    std::vector<std::string> getPieces() const;

    std::string getFileName() const;

    std::string getInfoHash() const;

    long long getPieceLength() const;

    long long getLength() const;

};