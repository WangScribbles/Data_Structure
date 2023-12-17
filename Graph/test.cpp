#include <iostream>
#include "Graph_matrix"
#include "Graph_table"
using namespace std;

int main()
{
	matrix::TestGraph();
	matrix::TestBDFS();
	
	link_table::TestGraph();
	
	return 0;
}