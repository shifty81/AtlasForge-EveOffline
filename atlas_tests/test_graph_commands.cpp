#include "../engine/command/CommandHistory.h"
#include "../engine/command/GraphCommands.h"
#include "../engine/sound/SoundGraph.h"
#include "../engine/sound/SoundNodes.h"
#include <iostream>
#include <cassert>

using SGraph = atlas::sound::SoundGraph;
using SNode = atlas::sound::SoundNode;
using SNodeID = atlas::sound::SoundNodeID;
using SEdge = atlas::sound::SoundEdge;

using AddNodeCmd = atlas::command::AddNodeCommand<SGraph, SNode, SNodeID>;
using RemoveNodeCmd = atlas::command::RemoveNodeCommand<SGraph, SNode, SNodeID>;
using AddEdgeCmd = atlas::command::AddEdgeCommand<SGraph, SEdge>;
using RemoveEdgeCmd = atlas::command::RemoveEdgeCommand<SGraph, SEdge>;

void test_graph_cmd_add_node() {
    SGraph graph;
    atlas::command::CommandHistory history;

    auto cmd = std::make_unique<AddNodeCmd>(graph,
        []() { return std::make_unique<atlas::sound::OscillatorNode>(); });
    history.Execute(std::move(cmd));

    assert(graph.NodeCount() == 1);
    std::cout << "[PASS] test_graph_cmd_add_node" << std::endl;
}

void test_graph_cmd_add_node_undo() {
    SGraph graph;
    atlas::command::CommandHistory history;

    history.Execute(std::make_unique<AddNodeCmd>(graph,
        []() { return std::make_unique<atlas::sound::OscillatorNode>(); }));
    assert(graph.NodeCount() == 1);

    history.Undo();
    assert(graph.NodeCount() == 0);
    std::cout << "[PASS] test_graph_cmd_add_node_undo" << std::endl;
}

void test_graph_cmd_add_node_redo() {
    SGraph graph;
    atlas::command::CommandHistory history;

    history.Execute(std::make_unique<AddNodeCmd>(graph,
        []() { return std::make_unique<atlas::sound::OscillatorNode>(); }));
    history.Undo();
    assert(graph.NodeCount() == 0);

    history.Redo();
    assert(graph.NodeCount() == 1);
    std::cout << "[PASS] test_graph_cmd_add_node_redo" << std::endl;
}

void test_graph_cmd_remove_node() {
    SGraph graph;
    atlas::command::CommandHistory history;

    auto id = graph.AddNode(std::make_unique<atlas::sound::OscillatorNode>());
    assert(graph.NodeCount() == 1);

    history.Execute(std::make_unique<RemoveNodeCmd>(graph, id,
        []() { return std::make_unique<atlas::sound::OscillatorNode>(); }));
    assert(graph.NodeCount() == 0);
    std::cout << "[PASS] test_graph_cmd_remove_node" << std::endl;
}

void test_graph_cmd_remove_node_undo() {
    SGraph graph;
    atlas::command::CommandHistory history;

    auto id = graph.AddNode(std::make_unique<atlas::sound::OscillatorNode>());
    assert(graph.NodeCount() == 1);

    history.Execute(std::make_unique<RemoveNodeCmd>(graph, id,
        []() { return std::make_unique<atlas::sound::OscillatorNode>(); }));
    assert(graph.NodeCount() == 0);

    history.Undo();
    assert(graph.NodeCount() == 1);
    std::cout << "[PASS] test_graph_cmd_remove_node_undo" << std::endl;
}

void test_graph_cmd_add_edge() {
    SGraph graph;
    atlas::command::CommandHistory history;

    auto oscId = graph.AddNode(std::make_unique<atlas::sound::OscillatorNode>());
    auto gainId = graph.AddNode(std::make_unique<atlas::sound::GainNode>());

    SEdge edge{oscId, 0, gainId, 0};
    history.Execute(std::make_unique<AddEdgeCmd>(graph, edge));

    assert(graph.Compile());
    atlas::sound::SoundContext ctx{44100, 128, 0};
    assert(graph.Execute(ctx));

    auto* output = graph.GetOutput(gainId, 0);
    assert(output != nullptr);
    std::cout << "[PASS] test_graph_cmd_add_edge" << std::endl;
}

void test_graph_cmd_add_edge_undo() {
    SGraph graph;
    atlas::command::CommandHistory history;

    auto oscId = graph.AddNode(std::make_unique<atlas::sound::OscillatorNode>());
    auto gainId = graph.AddNode(std::make_unique<atlas::sound::GainNode>());

    SEdge edge{oscId, 0, gainId, 0};
    history.Execute(std::make_unique<AddEdgeCmd>(graph, edge));
    history.Undo();

    // Graph should compile without the edge (nodes are independent)
    assert(graph.Compile());
    std::cout << "[PASS] test_graph_cmd_add_edge_undo" << std::endl;
}

void test_graph_cmd_remove_edge() {
    SGraph graph;
    atlas::command::CommandHistory history;

    auto oscId = graph.AddNode(std::make_unique<atlas::sound::OscillatorNode>());
    auto gainId = graph.AddNode(std::make_unique<atlas::sound::GainNode>());

    SEdge edge{oscId, 0, gainId, 0};
    graph.AddEdge(edge);

    history.Execute(std::make_unique<RemoveEdgeCmd>(graph, edge));

    // Should compile fine with no edges
    assert(graph.Compile());
    std::cout << "[PASS] test_graph_cmd_remove_edge" << std::endl;
}

void test_graph_cmd_remove_edge_undo() {
    SGraph graph;
    atlas::command::CommandHistory history;

    auto oscId = graph.AddNode(std::make_unique<atlas::sound::OscillatorNode>());
    auto gainId = graph.AddNode(std::make_unique<atlas::sound::GainNode>());

    SEdge edge{oscId, 0, gainId, 0};
    graph.AddEdge(edge);

    history.Execute(std::make_unique<RemoveEdgeCmd>(graph, edge));
    history.Undo();

    // Edge should be restored; compile and execute the chain
    assert(graph.Compile());
    atlas::sound::SoundContext ctx{44100, 128, 0};
    assert(graph.Execute(ctx));

    auto* output = graph.GetOutput(gainId, 0);
    assert(output != nullptr);
    std::cout << "[PASS] test_graph_cmd_remove_edge_undo" << std::endl;
}

void test_graph_cmd_sequence() {
    SGraph graph;
    atlas::command::CommandHistory history;

    // Add two nodes via commands
    history.Execute(std::make_unique<AddNodeCmd>(graph,
        []() { return std::make_unique<atlas::sound::OscillatorNode>(); }));
    assert(graph.NodeCount() == 1);

    history.Execute(std::make_unique<AddNodeCmd>(graph,
        []() { return std::make_unique<atlas::sound::GainNode>(); }));
    assert(graph.NodeCount() == 2);

    // Undo gain node
    history.Undo();
    assert(graph.NodeCount() == 1);

    // Undo oscillator node
    history.Undo();
    assert(graph.NodeCount() == 0);

    // Redo both nodes
    history.Redo();
    assert(graph.NodeCount() == 1);
    history.Redo();
    assert(graph.NodeCount() == 2);

    // Undo one, then execute a new command to clear redo stack
    history.Undo();
    assert(graph.NodeCount() == 1);
    assert(history.CanRedo());

    history.Execute(std::make_unique<AddNodeCmd>(graph,
        []() { return std::make_unique<atlas::sound::GainNode>(); }));
    assert(!history.CanRedo());
    assert(graph.NodeCount() == 2);

    std::cout << "[PASS] test_graph_cmd_sequence" << std::endl;
}
