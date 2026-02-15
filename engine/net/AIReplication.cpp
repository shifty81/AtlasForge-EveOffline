#include "AIReplication.h"

namespace atlas::net {

void AIReplicationManager::QueueStateSync(const AIStatePacket& packet) {
    m_outStates.push_back(packet);
}

void AIReplicationManager::QueueSignalUpdate(const AISignalPacket& packet) {
    m_outSignals.push_back(packet);
}

void AIReplicationManager::QueueMemorySync(const AIMemoryPacket& packet) {
    m_outMemories.push_back(packet);
}

std::vector<AIStatePacket> AIReplicationManager::FlushStatePackets() {
    std::vector<AIStatePacket> result = std::move(m_outStates);
    m_outStates.clear();
    return result;
}

std::vector<AISignalPacket> AIReplicationManager::FlushSignalPackets() {
    std::vector<AISignalPacket> result = std::move(m_outSignals);
    m_outSignals.clear();
    return result;
}

std::vector<AIMemoryPacket> AIReplicationManager::FlushMemoryPackets() {
    std::vector<AIMemoryPacket> result = std::move(m_outMemories);
    m_outMemories.clear();
    return result;
}

void AIReplicationManager::ApplyStatePacket(const AIStatePacket& packet) {
    m_receivedStates.push_back(packet);
}

void AIReplicationManager::ApplySignalPacket(const AISignalPacket& packet) {
    m_receivedSignals.push_back(packet);
}

void AIReplicationManager::ApplyMemoryPacket(const AIMemoryPacket& packet) {
    m_receivedMemories.push_back(packet);
}

const std::vector<AIStatePacket>& AIReplicationManager::ReceivedStates() const {
    return m_receivedStates;
}

const std::vector<AISignalPacket>& AIReplicationManager::ReceivedSignals() const {
    return m_receivedSignals;
}

const std::vector<AIMemoryPacket>& AIReplicationManager::ReceivedMemories() const {
    return m_receivedMemories;
}

size_t AIReplicationManager::PendingStateCount() const {
    return m_outStates.size();
}

size_t AIReplicationManager::PendingSignalCount() const {
    return m_outSignals.size();
}

size_t AIReplicationManager::PendingMemoryCount() const {
    return m_outMemories.size();
}

void AIReplicationManager::Clear() {
    m_outStates.clear();
    m_outSignals.clear();
    m_outMemories.clear();
    m_receivedStates.clear();
    m_receivedSignals.clear();
    m_receivedMemories.clear();
}

}
