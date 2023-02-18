#include <iostream>
#include <vector>
#include <forward_list>

#include "Graph_code.hpp"

void menu()
{
	Graph<double> g;

	int selection = 0;
	do
	{
		std::cout << std::endl << "---GRAPH DEMO:---" << std::endl << std::endl;
		std::cout << "0) Generate a demo graph as for graph_demo_0.png. This graph contains a negative cycle." << std::endl;
		std::cout << "1) Generate a demo graph as for graph_demo_1.png. This graph has only positive edges." << std::endl;
		std::cout << "2) Generate a demo graph as for graph_demo_2.png.This graph has positive and negative edges." << std::endl;
		std::cout << "3) Print the loaded graph on standard output" << std::endl;
		std::cout << "4) Execute and print results of Dijkstra Algorithm on the graph" << std::endl;
		std::cout << "5) Execute and print results of Bellman-Ford Algorithm on the graph" << std::endl;
		std::cout << "6) Exit demo" << std::endl << std::endl;
		std::cin >> selection;
		switch (selection)
		{
		case 0:
		{
			//GRAPH for BELLMAN-FORD testing, as for graph_demo_0.png 

			//std::cout << "graph_demo_0 has been loaded and is ready." << std::endl;
			break;
		}
		case 1:
		{
			//GRAPH for DIJKSTRA testing, as for graph_demo_1.png 
			//g.addEdge(0, 1, 4);
			//g.addEdge(0, 2, 2);
			g.addEdge(0, 1, 2);
			g.addEdge(0, 2, 4);
			g.addEdge(1, 2, 3);
			g.addEdge(1, 3, 2);
			g.addEdge(1, 4, 3);
			g.addEdge(2, 1, 1);
			g.addEdge(2, 3, 4);
			g.addEdge(2, 4, 5);
			g.addEdge(4, 3, 1);

			std::cout << "graph_demo_1 has been loaded and is ready." << std::endl;
			break;
		}
		case 2:
		{
			//GRAPH for BELLMAN-FORD testing, as for graph_demo_1.png 
			//add vertices

			//add edges

			//std::cout << "graph_demo_2 has been loaded and is ready." << std::endl;
			break;
		}
		case 3:
		{
			//stampa tutti i vertici e tutti gli archi
			for (auto it = g.begin(); it != g.end(); ++it)
			{
				std::cout << "Vertex " << *it << " has edges: \n";
				for (auto it2 = g.begin(*it); it2 != g.end(*it); ++it2)
				{
					// Operazioni sull'arco corrente
					auto prova = *it2;
					int dst = prova.first;
					double weight = prova.second;
					std::cout << *it << " -> " << dst << ", with weight: " << weight << "\n";
				}
				std::cout << std::endl;
			}
			break;
		}
		case 4:
		{
			std::string src = "";
			std::cout << "Source vertex: " << std::endl;
			std::cin >> src;
			auto res = Graph<double>::dijkstra(g, 0);
			for (int i = 0; i < res.size(); ++i)
			{
				std::cout << "Total cost from " << src << " to " << i << " is: " << res[i] << "\n";
			}
			break;
		}
		case 5:
		{
			/*
			std::string src = "";
			std::cout << "Source vertex: " << std::endl;
			std::cin >> src;
			auto res = Graph<std::string>::bellmanFord(g, src);
			for (auto it = res.begin(); it != res.end(); ++it)
			{
				std::cout << it->first << " " << it->second << std::endl;
			}
			break;
			*/
		}
		case 6:
		{
			std::cout << "exiting demo..." << std::endl;
		}

		}
	} while (selection != 6);

}

int main()
{
	menu();
	
	return 0;
}





