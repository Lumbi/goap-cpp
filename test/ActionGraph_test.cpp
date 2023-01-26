#include "../src/ActionGraph.h"

#include <algorithm>
#include "Assert.h"

void test__empty_graph__has_no_nodes()
{
    ActionGraph graph({});
    ASSERT_EQUAL(graph.get_nodes().empty(), true, "Empty graph should have no nodes");
}

void test__graph_no_successor()
{
    ActionGraph graph({ Action({}, {}) });
    ASSERT_EQUAL(graph.get_nodes().size(), 1, "Graph of one action has one node");

    auto node = graph.get_nodes().at(0);
    ASSERT_EQUAL(node->get_successors().empty(), true, "Node in graph of one empty action has no successor");
}

void test__graph_one_successor()
{
    Action first({ }, { Condition(1, true) });
    Action second({ Condition(1, true) }, { Condition(1, true) });
    ActionGraph graph({ first, second });

    ASSERT_EQUAL(graph.get_nodes().size(), 2, "Graph should have 2 nodes");
    ASSERT_EQUAL(graph.get_nodes().at(0)->get_successors().size(), 1, "The first node should have 1 successors");
    ASSERT_EQUAL(graph.get_nodes().at(1)->get_successors().size(), 1, "The second node should have 1 successor");
}

void test__graph_multiple_successors()
{
    Action first({ Condition(999, false) }, { Condition(1, true) });
    Action second({ Condition(1, true) }, { Condition(1, true) });
    Action third({ Condition(1, true) }, { Condition(3, false) });
    ActionGraph graph({ first, second, third });

    ASSERT_EQUAL(graph.get_nodes().size(), 3, "Graph should have 3 nodes");
    ASSERT_EQUAL(graph.get_nodes().at(0)->get_successors().size(), 2, "The first node should have 2 successors");
    ASSERT_EQUAL(graph.get_nodes().at(1)->get_successors().size(), 1, "The second node should have 1 successor");
    ASSERT_EQUAL(graph.get_nodes().at(2)->get_successors().size(), 0, "The third node should have 0 successor");
}

int ActionGraph_test(int, char**)
{
    test__empty_graph__has_no_nodes();
    test__graph_no_successor();
    test__graph_multiple_successors();

    return 0;
}
