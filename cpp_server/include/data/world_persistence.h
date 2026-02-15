#ifndef EVE_DATA_WORLD_PERSISTENCE_H
#define EVE_DATA_WORLD_PERSISTENCE_H

#include "ecs/world.h"
#include <string>
#include <cstdint>

namespace atlas {
namespace data {

/**
 * @brief Serializes and deserializes world state for persistent worlds
 *
 * Saves all entity data (position, velocity, health, capacitor, ship,
 * faction, AI, weapon, target, wormhole, fleet membership, station,
 * docked, wreck, captain personality, fleet morale, captain relationship,
 * emotional state, captain memory, fleet formation, fleet cargo pool,
 * rumor log, mineral deposit, system resources, market hub) to a JSON
 * file and restores it on load.
 */
class WorldPersistence {
public:
    WorldPersistence() = default;
    ~WorldPersistence() = default;

    /// Save the entire world state to a JSON file.
    /// @return true on success
    bool saveWorld(const ecs::World* world, const std::string& filepath);

    /// Load world state from a JSON file, creating entities and components.
    /// Existing entities are NOT cleared – call world->destroyEntity() first
    /// if a clean reload is desired.
    /// @return true on success, false on file-not-found or parse error
    bool loadWorld(ecs::World* world, const std::string& filepath);

    /// Serialize world state to a JSON string (useful for tests and network).
    std::string serializeWorld(const ecs::World* world) const;

    /// Deserialize a JSON string into the world.
    bool deserializeWorld(ecs::World* world, const std::string& json) const;

    /// Save world state to a compressed binary file (.atlasw).
    /// Uses a simple compression scheme: 4-byte magic, 4-byte uncompressed
    /// size, 4-byte compressed size, 4-byte checksum, then compressed data.
    bool saveWorldCompressed(const ecs::World* world, const std::string& filepath);

    /// Load world state from a compressed binary file.
    bool loadWorldCompressed(ecs::World* world, const std::string& filepath);

    /// Compress a string using simple run-length encoding.
    static std::string compress(const std::string& input);

    /// Decompress a run-length-encoded string.
    static std::string decompress(const std::string& input, uint32_t original_size);

    /// Compute a simple 32-bit checksum.
    static uint32_t checksum(const std::string& data);

private:
    /// Serialize a single entity to a JSON object string.
    std::string serializeEntity(const ecs::Entity* entity) const;

    /// Deserialize a single entity JSON object and create it in the world.
    bool deserializeEntity(ecs::World* world, const std::string& json) const;

    // Lightweight JSON helpers
    static std::string extractString(const std::string& json, const std::string& key);
    static float extractFloat(const std::string& json, const std::string& key, float fallback = 0.0f);
    static int extractInt(const std::string& json, const std::string& key, int fallback = 0);
    static double extractDouble(const std::string& json, const std::string& key, double fallback = 0.0);
    static bool extractBool(const std::string& json, const std::string& key, bool fallback = false);
    static std::string extractObject(const std::string& json, const std::string& key);
};

} // namespace data
} // namespace atlas

#endif // EVE_DATA_WORLD_PERSISTENCE_H
