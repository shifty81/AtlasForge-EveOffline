#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace atlas::net {

enum class AIPacketType : uint16_t {
    AIStateSync = 100,       // Full AI state snapshot
    AIResultBroadcast = 101, // Single AI execution result
    AISignalUpdate = 102,    // Signal value change
    AIMemorySync = 103       // Memory state replication
};

struct AIStatePacket {
    AIPacketType type = AIPacketType::AIStateSync;
    uint32_t tick = 0;
    uint32_t entityID = 0;
    std::string graphID;
    std::string action;
    float confidence = 0.0f;
};

struct AISignalPacket {
    AIPacketType type = AIPacketType::AISignalUpdate;
    uint32_t tick = 0;
    std::string signalName;
    float value = 0.0f;
};

struct AIMemoryPacket {
    AIPacketType type = AIPacketType::AIMemorySync;
    uint32_t tick = 0;
    uint32_t entityID = 0;
    std::string key;
    float strength = 0.0f;
    float decayRate = 0.0f;
};

class AIReplicationManager {
public:
    // Queue packets for sending
    void QueueStateSync(const AIStatePacket& packet);
    void QueueSignalUpdate(const AISignalPacket& packet);
    void QueueMemorySync(const AIMemoryPacket& packet);

    // Retrieve queued packets
    std::vector<AIStatePacket> FlushStatePackets();
    std::vector<AISignalPacket> FlushSignalPackets();
    std::vector<AIMemoryPacket> FlushMemoryPackets();

    // Receive and apply (client-side)
    void ApplyStatePacket(const AIStatePacket& packet);
    void ApplySignalPacket(const AISignalPacket& packet);
    void ApplyMemoryPacket(const AIMemoryPacket& packet);

    // Query applied state
    const std::vector<AIStatePacket>& ReceivedStates() const;
    const std::vector<AISignalPacket>& ReceivedSignals() const;
    const std::vector<AIMemoryPacket>& ReceivedMemories() const;

    size_t PendingStateCount() const;
    size_t PendingSignalCount() const;
    size_t PendingMemoryCount() const;

    void Clear();

private:
    // Outbound queues (server-side)
    std::vector<AIStatePacket> m_outStates;
    std::vector<AISignalPacket> m_outSignals;
    std::vector<AIMemoryPacket> m_outMemories;

    // Received state (client-side)
    std::vector<AIStatePacket> m_receivedStates;
    std::vector<AISignalPacket> m_receivedSignals;
    std::vector<AIMemoryPacket> m_receivedMemories;
};

}
