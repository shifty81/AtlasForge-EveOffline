#include "../engine/ai/AIGraphSandbox.h"
#include <iostream>
#include <cassert>

using namespace atlas::ai;

void test_sandbox_propose() {
    AIGraphSandbox sandbox;
    atlas::graphvm::GraphDiffResult diff;
    diff.nodeDiffs.push_back({atlas::graphvm::DiffAction::Added, 1, "TestNode"});

    uint32_t id = sandbox.Propose("graph1", "StrategyGraph", "Add node", diff, 100);
    assert(id > 0);
    assert(sandbox.TotalCount() == 1);
    assert(sandbox.PendingCount() == 1);

    std::cout << "[PASS] test_sandbox_propose" << std::endl;
}

void test_sandbox_approve() {
    AIGraphSandbox sandbox;
    atlas::graphvm::GraphDiffResult diff;
    diff.nodeDiffs.push_back({atlas::graphvm::DiffAction::Added, 1, "TestNode"});

    uint32_t id = sandbox.Propose("graph1", "StrategyGraph", "Add node", diff, 100);
    assert(sandbox.Approve(id, 110));
    assert(sandbox.PendingCount() == 0);

    const SandboxProposal* p = sandbox.GetProposal(id);
    assert(p != nullptr);
    assert(p->status == SandboxProposalStatus::Approved);
    assert(p->resolvedTick == 110);

    std::cout << "[PASS] test_sandbox_approve" << std::endl;
}

void test_sandbox_reject() {
    AIGraphSandbox sandbox;
    atlas::graphvm::GraphDiffResult diff;

    uint32_t id = sandbox.Propose("graph1", "WorldGraph", "Remove node", diff, 200);
    assert(sandbox.Reject(id, 210));

    const SandboxProposal* p = sandbox.GetProposal(id);
    assert(p != nullptr);
    assert(p->status == SandboxProposalStatus::Rejected);
    assert(p->resolvedTick == 210);

    std::cout << "[PASS] test_sandbox_reject" << std::endl;
}

void test_sandbox_double_approve() {
    AIGraphSandbox sandbox;
    atlas::graphvm::GraphDiffResult diff;

    uint32_t id = sandbox.Propose("g", "T", "desc", diff, 100);
    assert(sandbox.Approve(id, 110));
    // Cannot approve again — already approved
    assert(!sandbox.Approve(id, 120));

    std::cout << "[PASS] test_sandbox_double_approve" << std::endl;
}

void test_sandbox_get_by_status() {
    AIGraphSandbox sandbox;
    atlas::graphvm::GraphDiffResult diff;

    sandbox.Propose("g1", "T", "a", diff, 100);
    sandbox.Propose("g2", "T", "b", diff, 101);
    uint32_t id3 = sandbox.Propose("g3", "T", "c", diff, 102);
    sandbox.Approve(id3, 110);

    auto pending = sandbox.GetByStatus(SandboxProposalStatus::Pending);
    assert(pending.size() == 2);

    auto approved = sandbox.GetByStatus(SandboxProposalStatus::Approved);
    assert(approved.size() == 1);

    std::cout << "[PASS] test_sandbox_get_by_status" << std::endl;
}

void test_sandbox_get_by_graph() {
    AIGraphSandbox sandbox;
    atlas::graphvm::GraphDiffResult diff;

    sandbox.Propose("graph1", "T", "a", diff, 100);
    sandbox.Propose("graph1", "T", "b", diff, 101);
    sandbox.Propose("graph2", "T", "c", diff, 102);

    auto g1 = sandbox.GetByGraph("graph1");
    assert(g1.size() == 2);

    auto g2 = sandbox.GetByGraph("graph2");
    assert(g2.size() == 1);

    auto g3 = sandbox.GetByGraph("missing");
    assert(g3.empty());

    std::cout << "[PASS] test_sandbox_get_by_graph" << std::endl;
}

void test_sandbox_purge_resolved() {
    AIGraphSandbox sandbox;
    atlas::graphvm::GraphDiffResult diff;

    sandbox.Propose("g1", "T", "a", diff, 100);
    uint32_t id2 = sandbox.Propose("g2", "T", "b", diff, 101);
    uint32_t id3 = sandbox.Propose("g3", "T", "c", diff, 102);

    sandbox.Approve(id2, 110);
    sandbox.Reject(id3, 111);

    assert(sandbox.TotalCount() == 3);
    sandbox.PurgeResolved();
    assert(sandbox.TotalCount() == 1);
    assert(sandbox.PendingCount() == 1);

    std::cout << "[PASS] test_sandbox_purge_resolved" << std::endl;
}

void test_sandbox_clear() {
    AIGraphSandbox sandbox;
    atlas::graphvm::GraphDiffResult diff;

    sandbox.Propose("g1", "T", "a", diff, 100);
    sandbox.Propose("g2", "T", "b", diff, 101);
    assert(sandbox.TotalCount() == 2);

    sandbox.Clear();
    assert(sandbox.TotalCount() == 0);
    assert(sandbox.PendingCount() == 0);

    std::cout << "[PASS] test_sandbox_clear" << std::endl;
}
