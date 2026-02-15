#include <cassert>
#include <iostream>
#include "../engine/net/AIReplication.h"

using namespace atlas::net;

void test_ai_repl_queue_state() {
    AIReplicationManager mgr;
    AIStatePacket pkt;
    pkt.tick = 1;
    pkt.entityID = 42;
    pkt.graphID = "graph_a";
    pkt.action = "patrol";
    pkt.confidence = 0.8f;
    mgr.QueueStateSync(pkt);
    assert(mgr.PendingStateCount() == 1);
    std::cout << "[PASS] test_ai_repl_queue_state" << std::endl;
}

void test_ai_repl_flush_state() {
    AIReplicationManager mgr;
    AIStatePacket pkt;
    pkt.tick = 1;
    pkt.entityID = 10;
    mgr.QueueStateSync(pkt);
    assert(mgr.PendingStateCount() == 1);

    auto flushed = mgr.FlushStatePackets();
    assert(flushed.size() == 1);
    assert(flushed[0].entityID == 10);
    assert(mgr.PendingStateCount() == 0);
    std::cout << "[PASS] test_ai_repl_flush_state" << std::endl;
}

void test_ai_repl_queue_signal() {
    AIReplicationManager mgr;
    AISignalPacket pkt;
    pkt.tick = 5;
    pkt.signalName = "threat_level";
    pkt.value = 0.75f;
    mgr.QueueSignalUpdate(pkt);
    assert(mgr.PendingSignalCount() == 1);

    auto flushed = mgr.FlushSignalPackets();
    assert(flushed.size() == 1);
    assert(flushed[0].signalName == "threat_level");
    assert(mgr.PendingSignalCount() == 0);
    std::cout << "[PASS] test_ai_repl_queue_signal" << std::endl;
}

void test_ai_repl_queue_memory() {
    AIReplicationManager mgr;
    AIMemoryPacket pkt;
    pkt.tick = 3;
    pkt.entityID = 99;
    pkt.key = "last_target";
    pkt.strength = 1.0f;
    pkt.decayRate = 0.05f;
    mgr.QueueMemorySync(pkt);
    assert(mgr.PendingMemoryCount() == 1);

    auto flushed = mgr.FlushMemoryPackets();
    assert(flushed.size() == 1);
    assert(flushed[0].key == "last_target");
    assert(mgr.PendingMemoryCount() == 0);
    std::cout << "[PASS] test_ai_repl_queue_memory" << std::endl;
}

void test_ai_repl_apply_state() {
    AIReplicationManager mgr;
    AIStatePacket pkt;
    pkt.tick = 7;
    pkt.entityID = 1;
    pkt.action = "flee";
    mgr.ApplyStatePacket(pkt);

    const auto& received = mgr.ReceivedStates();
    assert(received.size() == 1);
    assert(received[0].action == "flee");
    std::cout << "[PASS] test_ai_repl_apply_state" << std::endl;
}

void test_ai_repl_apply_signal() {
    AIReplicationManager mgr;
    AISignalPacket pkt;
    pkt.tick = 2;
    pkt.signalName = "danger";
    pkt.value = 1.0f;
    mgr.ApplySignalPacket(pkt);

    const auto& received = mgr.ReceivedSignals();
    assert(received.size() == 1);
    assert(received[0].signalName == "danger");
    std::cout << "[PASS] test_ai_repl_apply_signal" << std::endl;
}

void test_ai_repl_apply_memory() {
    AIReplicationManager mgr;
    AIMemoryPacket pkt;
    pkt.tick = 4;
    pkt.entityID = 50;
    pkt.key = "ally_seen";
    pkt.strength = 0.9f;
    mgr.ApplyMemoryPacket(pkt);

    const auto& received = mgr.ReceivedMemories();
    assert(received.size() == 1);
    assert(received[0].key == "ally_seen");
    std::cout << "[PASS] test_ai_repl_apply_memory" << std::endl;
}

void test_ai_repl_clear() {
    AIReplicationManager mgr;

    AIStatePacket sp;
    sp.tick = 1;
    mgr.QueueStateSync(sp);
    mgr.ApplyStatePacket(sp);

    AISignalPacket sig;
    sig.tick = 1;
    mgr.QueueSignalUpdate(sig);
    mgr.ApplySignalPacket(sig);

    AIMemoryPacket mp;
    mp.tick = 1;
    mgr.QueueMemorySync(mp);
    mgr.ApplyMemoryPacket(mp);

    mgr.Clear();
    assert(mgr.PendingStateCount() == 0);
    assert(mgr.PendingSignalCount() == 0);
    assert(mgr.PendingMemoryCount() == 0);
    assert(mgr.ReceivedStates().empty());
    assert(mgr.ReceivedSignals().empty());
    assert(mgr.ReceivedMemories().empty());
    std::cout << "[PASS] test_ai_repl_clear" << std::endl;
}
