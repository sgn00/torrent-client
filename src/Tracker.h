#pragma once

#include <string>
#include "TorrentParser.h"

struct Peer {
    std::string ip;
    int port;
};

class Tracker {
private:

    std::string peerId;
    TorrentParser tp;
    
    static std::string generatePeerId();

    std::vector<Peer> decodeResponse(const std::string& str) const;

public:

    Tracker(const TorrentParser& _tp);

    std::vector<Peer> retrievePeers(int downloaded);

};
