#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "../graphvm/GraphDiff.h"

namespace atlas::ai {

/// Status of a sandbox proposal.
enum class SandboxProposalStatus : uint8_t {
    Pending,
    Approved,
    Rejected
};

/// A single proposed graph change from an AI system.
/// Contains the diff and metadata about the proposal.
struct SandboxProposal {
    uint32_t id = 0;
    std::string graphId;
    std::string graphType;
    std::string description;
    graphvm::GraphDiffResult diff;
    SandboxProposalStatus status = SandboxProposalStatus::Pending;
    uint64_t proposedTick = 0;
    uint64_t resolvedTick = 0;
};

/// AI Graph Authoring Sandbox — safe, diff-only, human-approved graph editing.
/// AI systems propose changes as graph diffs. Changes are staged in a sandbox
/// and only applied after explicit human approval.
/// AI is never an authority — AI proposes, humans approve, commands execute.
class AIGraphSandbox {
public:
    /// Submit a new proposal to the sandbox. Returns the proposal ID.
    uint32_t Propose(const std::string& graphId, const std::string& graphType,
                     const std::string& description,
                     const graphvm::GraphDiffResult& diff, uint64_t tick);

    /// Approve a pending proposal by ID. Returns true if found and was pending.
    bool Approve(uint32_t proposalId, uint64_t tick);

    /// Reject a pending proposal by ID. Returns true if found and was pending.
    bool Reject(uint32_t proposalId, uint64_t tick);

    /// Get a proposal by ID. Returns nullptr if not found.
    const SandboxProposal* GetProposal(uint32_t proposalId) const;

    /// Get all proposals with a given status.
    std::vector<const SandboxProposal*> GetByStatus(SandboxProposalStatus status) const;

    /// Get all proposals for a specific graph.
    std::vector<const SandboxProposal*> GetByGraph(const std::string& graphId) const;

    /// Get count of pending proposals.
    size_t PendingCount() const;

    /// Get total proposal count.
    size_t TotalCount() const;

    /// Remove all resolved (approved/rejected) proposals.
    void PurgeResolved();

    /// Clear all proposals.
    void Clear();

private:
    std::vector<SandboxProposal> m_proposals;
    uint32_t m_nextId = 1;
};

} // namespace atlas::ai
