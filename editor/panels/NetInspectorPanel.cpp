#include "NetInspectorPanel.h"

namespace atlas::editor {

void NetInspectorPanel::Draw() {
    Refresh();
    // Rendering is handled by the Atlas UI system when connected.
    // The cached data (mode name, authority flag, peer list) is available
    // for the UI layer to read and present.
}

void NetInspectorPanel::Refresh() {
    m_peerCache.clear();
    auto& peers = m_net.Peers();
    m_peerCache.reserve(peers.size());
    for (auto& p : peers) {
        PeerSnapshot snap;
        snap.id = p.id;
        snap.rtt = p.rtt;
        snap.connected = p.connected;
        m_peerCache.push_back(snap);
    }
}

std::string NetInspectorPanel::ModeName() const {
    switch (m_net.Mode()) {
        case net::NetMode::Standalone: return "Standalone";
        case net::NetMode::Client:     return "Client";
        case net::NetMode::Server:     return "Server";
        case net::NetMode::P2P_Host:   return "P2P_Host";
        case net::NetMode::P2P_Peer:   return "P2P_Peer";
        default:                       return "Unknown";
    }
}

bool NetInspectorPanel::IsAuthority() const {
    return m_net.IsAuthority();
}

}
