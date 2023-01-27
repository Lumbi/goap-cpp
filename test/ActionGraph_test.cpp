#include "../src/ActionGraph.h"

#include "Assert.h"
#include "../src/Action.h"
#include "../src/Goal.h"
#include "../src/ActionGraph.h"
#include "../src/ActionPath.h"

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

void test__find_path__emtpy_graph()
{
    ActionGraph graph({});
    Goal goal({});
    auto path = graph.find_path({}, goal);
    ASSERT_NULL(path, "There should be no path to goal on an empty graph");
}

void test__find_path__no_path()
{
    Action first({}, { Condition(1, true) });
    Action second({ Condition(1, true) }, { Condition(1, true) });
    Action third({ Condition(1, true) }, { Condition(3, false) });
    ActionGraph graph({ first, second, third });
    Goal goal({ Condition(777, true) });
    auto path = graph.find_path({}, goal);

    ASSERT_NULL(path, "There should be no path to goal with condition that cannot be reached");
}

void test__find_path__single_path()
{
    Action first("first", {}, { Condition(1, true) });
    Action second("second", { Condition(1, true) }, { Condition(1, true) });
    Action third("third", { Condition(1, true) }, { Condition(3, false) });
    ActionGraph graph({ first, second, third });
    Goal goal({ Condition(3, false) });
    auto path = graph.find_path({}, goal);

    ASSERT_NOT_NULL(path, "A path should be found");
    ASSERT_EQUAL(path->get_actions().size(), 3, "The path should have 3 actions");
    ASSERT_EQUAL(path->get_actions().at(0).get_name(), "first", "The 1st action should be correct");
    ASSERT_EQUAL(path->get_actions().at(1).get_name(), "second", "The 2nd action should be correct");
    ASSERT_EQUAL(path->get_actions().at(2).get_name(), "third", "The 3rd action should be correct");
}

void test__find_path__multiple_paths()
{
    Action first("first", {}, { Condition(1, true), Condition(3, false) });
    Action second("second", { Condition(1, true) }, { Condition(1, true) });
    Action third("third", { Condition(1, true) }, { Condition(3, false) });
    ActionGraph graph({ first, second, third });
    Goal goal({ Condition(3, false) });
    auto path = graph.find_path({}, goal);

    ASSERT_NOT_NULL(path, "The shortest path should be found");
    ASSERT_EQUAL(path->get_actions().size(), 1, "The path should have 1 action");
    ASSERT_EQUAL(path->get_actions().at(0).get_name(), "first", "The 1st action should be correct");
}

int ActionGraph_test(int, char**)
{
    test__empty_graph__has_no_nodes();
    test__graph_no_successor();
    test__graph_multiple_successors();
    test__find_path__emtpy_graph();
    test__find_path__no_path();
    test__find_path__single_path();
    test__find_path__multiple_paths();

    return 0;
}
