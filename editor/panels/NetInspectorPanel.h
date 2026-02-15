#pragma once
#include "../ui/EditorPanel.h"
#include "../../engine/net/NetContext.h"
#include <string>
#include <vector>

namespace atlas::editor {

class NetInspectorPanel : public EditorPanel {
public:
    explicit NetInspectorPanel(net::NetContext& net) : m_net(net) {}

    const char* Name() const override { return "Network"; }
    void Draw() override;

    /// Refresh cached network state.
    void Refresh();

    /// Snapshot of a connected peer for display.
    struct PeerSnapshot {
        uint32_t id = 0;
        float rtt = 0.0f;
        bool connected = false;
    };

    std::string ModeName() const;
    bool IsAuthority() const;
    const std::vector<PeerSnapshot>& GetPeers() const { return m_peerCache; }
    size_t PeerCount() const { return m_peerCache.size(); }

private:
    net::NetContext& m_net;
    std::vector<PeerSnapshot> m_peerCache;
};

}
