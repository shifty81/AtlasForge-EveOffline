#include "AIGraphSandbox.h"
#include <algorithm>

namespace atlas::ai {

uint32_t AIGraphSandbox::Propose(const std::string& graphId, const std::string& graphType,
                                  const std::string& description,
                                  const graphvm::GraphDiffResult& diff, uint64_t tick) {
    SandboxProposal proposal;
    proposal.id = m_nextId++;
    proposal.graphId = graphId;
    proposal.graphType = graphType;
    proposal.description = description;
    proposal.diff = diff;
    proposal.status = SandboxProposalStatus::Pending;
    proposal.proposedTick = tick;
    proposal.resolvedTick = 0;
    uint32_t id = proposal.id;
    m_proposals.push_back(std::move(proposal));
    return id;
}

bool AIGraphSandbox::Approve(uint32_t proposalId, uint64_t tick) {
    for (auto& p : m_proposals) {
        if (p.id == proposalId && p.status == SandboxProposalStatus::Pending) {
            p.status = SandboxProposalStatus::Approved;
            p.resolvedTick = tick;
            return true;
        }
    }
    return false;
}

bool AIGraphSandbox::Reject(uint32_t proposalId, uint64_t tick) {
    for (auto& p : m_proposals) {
        if (p.id == proposalId && p.status == SandboxProposalStatus::Pending) {
            p.status = SandboxProposalStatus::Rejected;
            p.resolvedTick = tick;
            return true;
        }
    }
    return false;
}

const SandboxProposal* AIGraphSandbox::GetProposal(uint32_t proposalId) const {
    for (const auto& p : m_proposals) {
        if (p.id == proposalId) return &p;
    }
    return nullptr;
}

std::vector<const SandboxProposal*> AIGraphSandbox::GetByStatus(SandboxProposalStatus status) const {
    std::vector<const SandboxProposal*> result;
    for (const auto& p : m_proposals) {
        if (p.status == status) result.push_back(&p);
    }
    return result;
}

std::vector<const SandboxProposal*> AIGraphSandbox::GetByGraph(const std::string& graphId) const {
    std::vector<const SandboxProposal*> result;
    for (const auto& p : m_proposals) {
        if (p.graphId == graphId) result.push_back(&p);
    }
    return result;
}

size_t AIGraphSandbox::PendingCount() const {
    size_t count = 0;
    for (const auto& p : m_proposals) {
        if (p.status == SandboxProposalStatus::Pending) ++count;
    }
    return count;
}

size_t AIGraphSandbox::TotalCount() const {
    return m_proposals.size();
}

void AIGraphSandbox::PurgeResolved() {
    m_proposals.erase(
        std::remove_if(m_proposals.begin(), m_proposals.end(),
                       [](const SandboxProposal& p) {
                           return p.status != SandboxProposalStatus::Pending;
                       }),
        m_proposals.end());
}

void AIGraphSandbox::Clear() {
    m_proposals.clear();
    m_nextId = 1;
}

} // namespace atlas::ai
