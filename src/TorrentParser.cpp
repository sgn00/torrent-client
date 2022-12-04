#include "TorrentParser.h"
#include <sha1.hpp>

TorrentParser::TorrentParser(const std::string& _f) : fileName(_f) {
    std::ifstream fileStream(fileName, std::ifstream::binary);
    auto data = bencode::decode(fileStream);
    value = std::get<bencode::dict>(data);
    info = std::get<bencode::dict>(value.at("info"));

    SHA1 shaCalc;
    shaCalc.update(bencode::encode(info));
    infoHash = shaCalc.final();
    // auto val = std::get<bencode::string>(value["cow"]);
    // for (auto& p : value) {
    //     auto key = p.first;
    //     std::cout << key << std::endl;
    //     std::cout << std::get<bencode::string>(p.second) << std::endl;
    // }
}

std::string TorrentParser::getAnnounce() const {
    return std::get<bencode::string>(value.at("announce"));
}

std::vector<std::string> TorrentParser::getPieces() const {
    auto pieces = std::get<bencode::string>(info.at("pieces"));
    std::vector<std::string> res;
    assert(pieces.size() % HASHLEN == 0);
    int numPieces = pieces.size() % HASHLEN;
    for (int i = 0; i < pieces.size(); i += HASHLEN) {
        res.push_back(pieces.substr(i, HASHLEN));
    }
    return res;
}

std::string TorrentParser::getFileName() const {
    return std::get<bencode::string>(info.at("name"));
}

std::string TorrentParser::getInfoHash() const {
    return infoHash;
}

long long TorrentParser::getPieceLength() const {
    return std::get<bencode::integer>(info.at("piece length"));
}

long long TorrentParser::getLength() const {
    return std::get<bencode::integer>(info.at("length"));
}

