#include "Tracker.h"
#include "util.h"
#include <cpr/cpr.h>
#include <string>

Tracker::Tracker(const TorrentParser& _tp) : tp(_tp), peerId(generatePeerId()) {
}

std::string Tracker::generatePeerId() {
    std::string res = "-PC0001-";
    for (int i = 0; i < 12; i++) {
        int j = rand() % 10;
        res.push_back(j + '0');
    }
    return res;
}


std::vector<Peer> Tracker::retrievePeers(int downloaded) {
    std::string announceUrl = tp.getAnnounce();
    std::string infoHash = tp.getInfoHash();
    std::string port = "6889";
    std::string bytesDownloaded = std::to_string(downloaded);
    std::string left = std::to_string(tp.getLength() - downloaded);
    cpr::Parameters p = {
        {"info_hash", std::string(hexDecode(infoHash))},
        {"peer_id", peerId},
        {"port", port},
        {"uploaded", "0"},
        {"downloaded", bytesDownloaded},
        {"left", left},
        {"compact", "1"}
    };

    cpr::Response res = cpr::Get(cpr::Url{announceUrl}, p);
    if (res.status_code != 200) {
        throw std::runtime_error("Error retrieving peers from tracker");
    }

    return decodeResponse(res.text);
}

std::vector<Peer> Tracker::decodeResponse(const std::string& str) const {
    std::vector<Peer> peers;
    auto decoded = bencode::decode(str);
    auto dict = std::get<bencode::dict>(decoded);
    auto peersVal = std::get<bencode::string>(dict.at("peers"));
    if (typeid(peersVal) == typeid(bencode::string)) {
        const int infoSize = 6;
        int peerNum = peersVal.size() / infoSize;
        for (int i = 0; i < peerNum; i++) {
            int offset = i * infoSize;
            std::stringstream peerIp;
            peerIp << std::to_string((uint8_t) peersVal[offset]) << ".";
            peerIp << std::to_string((uint8_t) peersVal[offset + 1]) << ".";
            peerIp << std::to_string((uint8_t) peersVal[offset + 2]) << ".";
            peerIp << std::to_string((uint8_t) peersVal[offset + 3]);
            int peerPort = bytesToInt(peersVal.substr(offset + 4, 2));
            Peer newPeer{ peerIp.str(), peerPort };
            peers.push_back(newPeer);
        }
    } else {
        throw std::runtime_error("Peers value from tracker not in supported format");
    }
    return {};
}