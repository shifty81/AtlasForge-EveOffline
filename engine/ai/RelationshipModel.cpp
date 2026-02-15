#include "RelationshipModel.h"
#include <algorithm>

namespace atlas::ai {

uint64_t RelationshipModel::MakeKey(uint64_t a, uint64_t b) {
    uint64_t lo = std::min(a, b);
    uint64_t hi = std::max(a, b);
    // Combine using Szudzik's pairing (fits in 64 bits for 32-bit entity IDs)
    return (hi << 32) | lo;
}

void RelationshipModel::Set(uint64_t entityA, uint64_t entityB, float value) {
    m_relationships[MakeKey(entityA, entityB)] = value;
}

float RelationshipModel::Get(uint64_t entityA, uint64_t entityB) const {
    auto it = m_relationships.find(MakeKey(entityA, entityB));
    if (it == m_relationships.end()) return 0.0f;
    return it->second;
}

void RelationshipModel::Modify(uint64_t entityA, uint64_t entityB, float delta) {
    uint64_t key = MakeKey(entityA, entityB);
    m_relationships[key] += delta;
}

bool RelationshipModel::Has(uint64_t entityA, uint64_t entityB) const {
    return m_relationships.count(MakeKey(entityA, entityB)) > 0;
}

void RelationshipModel::Remove(uint64_t entityA, uint64_t entityB) {
    m_relationships.erase(MakeKey(entityA, entityB));
}

void RelationshipModel::Clear() {
    m_relationships.clear();
}

size_t RelationshipModel::Count() const {
    return m_relationships.size();
}

}
