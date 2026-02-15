#include "../editor/panels/NetInspectorPanel.h"
#include "../engine/net/NetContext.h"
#include <iostream>
#include <cassert>

using namespace atlas::net;
using namespace atlas::editor;

void test_net_inspector_standalone() {
    NetContext net;
    net.Init(NetMode::Standalone);
    NetInspectorPanel panel(net);
    assert(panel.ModeName() == "Standalone");
    net.Shutdown();
    std::cout << "[PASS] test_net_inspector_standalone" << std::endl;
}

void test_net_inspector_server_mode() {
    NetContext net;
    net.Init(NetMode::Server);
    NetInspectorPanel panel(net);
    assert(panel.ModeName() == "Server");
    assert(panel.IsAuthority());
    net.Shutdown();
    std::cout << "[PASS] test_net_inspector_server_mode" << std::endl;
}

void test_net_inspector_client_mode() {
    NetContext net;
    net.Init(NetMode::Client);
    NetInspectorPanel panel(net);
    assert(panel.ModeName() == "Client");
    assert(!panel.IsAuthority());
    net.Shutdown();
    std::cout << "[PASS] test_net_inspector_client_mode" << std::endl;
}

void test_net_inspector_peer_list() {
    NetContext net;
    net.Init(NetMode::Server);
    net.AddPeer();
    net.AddPeer();
    NetInspectorPanel panel(net);
    panel.Refresh();
    assert(panel.PeerCount() == 2);
    net.Shutdown();
    std::cout << "[PASS] test_net_inspector_peer_list" << std::endl;
}

void test_net_inspector_draw_calls_refresh() {
    NetContext net;
    net.Init(NetMode::Server);
    net.AddPeer();
    NetInspectorPanel panel(net);
    assert(panel.PeerCount() == 0);
    panel.Draw();
    assert(panel.PeerCount() == 1);
    net.Shutdown();
    std::cout << "[PASS] test_net_inspector_draw_calls_refresh" << std::endl;
}
