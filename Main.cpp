#include <chrono>

#include "Graph.hpp"

void menu()
{
	Graph<double> g;

	int selection = 0;
	do
	{
		std::cout << std::endl << "---GRAPH DEMO:---" << std::endl << std::endl;
		std::cout << "0) Generate a demo graph as for 'Grafo 3'. This graph contains a negative cycle." << std::endl;
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
			g.reset();
			//GRAPH for BELLMAN-FORD testing, as for 'Grafo 0'
			g.addEdge(0, 4, 4);
			g.addEdge(1, 2, 7);
			g.addEdge(2, 4, -4);
			g.addEdge(3, 5, -6);
			g.addEdge(4, 3, 3);
			g.addEdge(5, 4, 5);
			g.addEdge(5, 0, 2);
			g.addEdge(5, 1, -8);

			std::cout << "'Grafo 0' has been loaded and is ready." << std::endl;
			break;
		}
		case 1:
		{
			g.reset();
			//GRAPH for DIJKSTRA testing, as for 'Grafo 1'
			g.addEdge(0, 1, 2);
			g.addEdge(0, 5, 3);
			g.addEdge(1, 2, 5);
			g.addEdge(2, 3, 7);
			g.addEdge(2, 4, 8);
			g.addEdge(3, 5, 4);
			g.addEdge(4, 1, 3);

			std::cout << "'Grafo 1' has been loaded and is ready." << std::endl;
			break;
		}
		case 2:
		{
			g.reset();
			//GRAPH for BELLMAN-FORD testing, as for 'Grafo 2'.png 
			g.addEdge(0, 3, -6);
			g.addEdge(0, 2, 6);
			g.addEdge(2, 4, 2);
			g.addEdge(2, 3, -1);
			g.addEdge(3, 1, 1);
			g.addEdge(4, 1, -4);
			g.addEdge(5, 0, 8);

			std::cout << "'Grafo 2' has been loaded and is ready." << std::endl;
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
					auto vrt = *it2;
					int dst = vrt.first;
					double weight = vrt.second;
					std::cout << *it << " -> " << dst << ", with weight: " << weight << "\n";
				}
				std::cout << std::endl;
			}
			break;
		}
		case 4:
		{
			int src = 0;
			std::cout << "Source vertex: " << std::endl;
			std::cin >> src;
			auto res = Graph<double>();
			auto tempo = 0;
			try
			{
				auto inizio = std::chrono::high_resolution_clock::now();
				res = Graph<double>::dijkstra(g, src);
				auto fine = std::chrono::high_resolution_clock::now();
				tempo = std::chrono::duration_cast<std::chrono::nanoseconds>(fine - inizio).count();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				break;
			}
			std::cout << "Single-source shortest path tree:\n";
			//stampa tutti i vertici e tutti gli archi
			for (auto it = res.begin(); it != res.end(); ++it)
			{
				std::cout << "Vertex " << *it << " has edges: \n";
				for (auto it2 = res.begin(*it); it2 != res.end(*it); ++it2)
				{
					// Operazioni sull'arco corrente
					auto prova = *it2;
					int dst = prova.first;
					double weight = prova.second;
					std::cout << *it << " -> " << dst << ", with weight: " << weight << "\n";
				}
				std::cout << std::endl;
			}
			std::cout << "Dijkstra algorithm took " << tempo << " nanoseconds to complete." << std::endl;

			break;
		}
		case 5:
		{
			int src = 0;
			std::cout << "Source vertex: " << std::endl;
			std::cin >> src;
			auto res = Graph<double>();
			auto tempo = 0;
			try
			{
				auto inizio = std::chrono::high_resolution_clock::now();
				res = Graph<double>::bellmanFord(g, src);
				auto fine = std::chrono::high_resolution_clock::now();
				tempo = std::chrono::duration_cast<std::chrono::nanoseconds>(fine - inizio).count();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				break;
			}
			//stampa tutti i vertici e tutti gli archi
			std::cout << "Single-source shortest path tree:\n";
			for (auto it = res.begin(); it != res.end(); ++it)
			{
				std::cout << "Vertex " << *it << " has edges: \n";
				for (auto it2 = res.begin(*it); it2 != res.end(*it); ++it2)
				{
					// Operazioni sull'arco corrente
					auto prova = *it2;
					int dst = prova.first;
					double weight = prova.second;
					std::cout << *it << " -> " << dst << ", with weight: " << weight << "\n";
				}
				std::cout << std::endl;
			}
			std::cout << "Bellman-Ford algorithm took " << tempo << " nanoseconds to complete." << std::endl;
			break;
		}
		case 6:
		{
			std::cout << "exiting demo..." << std::endl;
			break;
		}
		}
	} while (selection != 6);

}

int main()
{
	menu();

	return 0;
}




