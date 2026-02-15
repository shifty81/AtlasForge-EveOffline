#pragma once
#include "CommandHistory.h"
#include <functional>
#include <memory>
#include <string>

namespace atlas::command {

// Generic graph command for adding a node
// GraphT must have: AddNode(unique_ptr<NodeT>) -> IDT, RemoveNode(IDT)
template<typename GraphT, typename NodeT, typename IDT>
class AddNodeCommand : public Command {
public:
    using NodeFactory = std::function<std::unique_ptr<NodeT>()>;

    AddNodeCommand(GraphT& graph, NodeFactory factory)
        : m_graph(graph), m_factory(std::move(factory)), m_id{} {}

    void Execute() override {
        m_id = m_graph.AddNode(m_factory());
    }

    void Undo() override {
        m_graph.RemoveNode(m_id);
    }

    std::string Name() const override { return "AddNode"; }
    IDT GetID() const { return m_id; }

private:
    GraphT& m_graph;
    NodeFactory m_factory;
    IDT m_id;
};

// Generic graph command for removing a node
template<typename GraphT, typename NodeT, typename IDT>
class RemoveNodeCommand : public Command {
public:
    using NodeFactory = std::function<std::unique_ptr<NodeT>()>;

    RemoveNodeCommand(GraphT& graph, IDT id, NodeFactory factory)
        : m_graph(graph), m_id(id), m_factory(std::move(factory)) {}

    void Execute() override {
        m_graph.RemoveNode(m_id);
    }

    void Undo() override {
        m_id = m_graph.AddNode(m_factory());
    }

    std::string Name() const override { return "RemoveNode"; }

private:
    GraphT& m_graph;
    IDT m_id;
    NodeFactory m_factory;
};

// Generic graph command for adding an edge
template<typename GraphT, typename EdgeT>
class AddEdgeCommand : public Command {
public:
    AddEdgeCommand(GraphT& graph, const EdgeT& edge)
        : m_graph(graph), m_edge(edge) {}

    void Execute() override {
        m_graph.AddEdge(m_edge);
    }

    void Undo() override {
        m_graph.RemoveEdge(m_edge);
    }

    std::string Name() const override { return "AddEdge"; }

private:
    GraphT& m_graph;
    EdgeT m_edge;
};

// Generic graph command for removing an edge
template<typename GraphT, typename EdgeT>
class RemoveEdgeCommand : public Command {
public:
    RemoveEdgeCommand(GraphT& graph, const EdgeT& edge)
        : m_graph(graph), m_edge(edge) {}

    void Execute() override {
        m_graph.RemoveEdge(m_edge);
    }

    void Undo() override {
        m_graph.AddEdge(m_edge);
    }

    std::string Name() const override { return "RemoveEdge"; }

private:
    GraphT& m_graph;
    EdgeT m_edge;
};

} // namespace atlas::command
