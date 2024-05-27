#include "Graphs.h"
#include <cassert>
#include <stdexcept>
using namespace std;
using namespace graphs;

void demonstrate_optimal_warehouse() {
    Graph<string, double> graph;

    graph.add_vertex("1");
    graph.add_vertex("2");
    graph.add_vertex("3");
    graph.add_vertex("4");
    graph.add_vertex("5");
    graph.add_vertex("6");
    graph.add_vertex("7");

    graph.add_edge("1", "2", 13.0);
    graph.add_edge("1", "4", 23.0);
    graph.add_edge("1", "7", 14.0);

    graph.add_edge("2", "7", 21.0);
    graph.add_edge("2", "5", 11.0);
    graph.add_edge("2", "1", 17.0);

    graph.add_edge("3", "7", 5.0);
    graph.add_edge("3", "6", 23.0);
    graph.add_edge("3", "2", 21.0);

    graph.add_edge("4", "3", 41.0);
    graph.add_edge("4", "6", 21.0);

    graph.add_edge("5", "3", 13.0);
    graph.add_edge("5", "6", 12.0);

    graph.add_edge("6", "4", 17.0);
    graph.add_edge("6", "1", 13.0);
    graph.add_edge("6", "7", 23.0);

    graph.add_edge("7", "3", 16.0);

    cout << "Initial Graph:" << endl;
    graph.print_graph();
    cout << endl;

    string optimal_warehouse = graph.find_optimal_warehouse();
    cout << "The optimal location for the warehouse is: " << optimal_warehouse << endl;
}



void test_graph() {
    Graph<int, int> graph;

    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);

    assert(graph.has_vertex(1));
    assert(graph.has_vertex(2));
    assert(graph.has_vertex(3));
    assert(graph.has_vertex(4));

    graph.remove_vertex(4);
    assert(!graph.has_vertex(4));

    assert(graph.order() == 4);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, 10);
    graph.add_edge(1, 3, 20);
    graph.add_edge(2, 3, 5);

    assert(graph.has_edge(1, 2));
    assert(graph.has_edge(1, 3));
    assert(graph.has_edge(2, 3));

    assert(!graph.has_edge(3, 1));

    graph.remove_edge(1, 2);
    assert(!graph.has_edge(1, 2));

    auto shortest_path = graph.shortest_path(1, 3);
    for (const auto& edge : shortest_path) {
        cout << edge.from << " -> " << edge.to << " (Distance: " << edge.distance << ")" << endl;
    }

    //ПОДУМАЦ
    try {
        if (!(graph.degree(1) == 4)) {
            throw logic_error("Assertion failed: The degree of the node is not 4.");
        }
    }
    catch (const logic_error& e) {
        cerr << e.what() << std::endl;
    }

    assert(graph.degree(2) == 1);
    assert(graph.degree(3) == 0);

 
    auto walk = graph.walk(0);
    for (int i = 0; i < walk.size(); ++i) {
        cout << walk[i] << endl;
    }
  
    graph.print_graph();

}

int main() {
    //test_graph();
    demonstrate_optimal_warehouse();

    return 0;
}
