#include "Final.cpp"
#include <cassert>

void test_case_1()
{
    // create a PRC object
    PRC prc(2, 2);
    // create a graph
    prc.create_graph("samples/1/graph.txt");
    prc.process_parcels("samples/1/bookings.txt");
    prc.run_simulation(20);
    assert(prc.time_tick < 20);
    cout << "test 1 passed" << endl;
}

void test_case_2()
{
    // create a PRC object
    PRC prc(5, 5);
    // create a graph
    prc.create_graph("samples/3/graph.txt");
    prc.process_parcels("samples/3/bookings.txt");

    // read the graph file and check if the graph is created correctly
    assert(prc.graph.vertices.size() == 30);
    assert(prc.graph.edges.size() == 119);
    cout << "test 2 passed" << endl;
}

void test_case_3()
{
    // create a PRC object
    PRC prc(5, 5);
    // create a graph
    prc.create_graph("samples/4/graph.txt");
    prc.process_parcels("samples/4/bookings.txt");

    // check bfs
    std::vector<std::string> bfs_path = prc.graph.bfs("Mumbai", "Ahmedabad");
    assert(bfs_path.size() == 3);
    assert(bfs_path[0] == "Mumbai");
    assert(bfs_path[1] == "Nashik");
    assert(bfs_path[2] == "Ahmedabad");
    cout << "test 3 passed" << endl;
}

void test_case_4()
{
    // create a PRC object
    PRC prc(5, 5);
    // create a graph
    prc.create_graph("samples/1/graph.txt");
    prc.process_parcels("samples/1/bookings.txt");

    std::vector<std::string> dfs_path = prc.graph.dfs("Chennai", "Rohtak");
    
   
    assert(std::find(dfs_path.begin(), dfs_path.end(), "Tirupati") == dfs_path.end());
    cout << "test 4 passed" << endl;
}

int main()
{
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    return 0;
}
