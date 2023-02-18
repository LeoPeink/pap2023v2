#include "Graph.hpp"

/*
template <typename T>
void Graph<T>::removeVertex()	//PROBLEMA: rimuovendo un vertice gli altri scalano, perdendo i nomi dei grafi.
{
	std::cout << "I still do nothing! Implement me!";
}
*/

template <typename T>
void Graph<T>::addEdge(int src,int dst, T weigth)
{
	if (adj_list.size() <= src)
	{
		adj_list.resize(src+1);
	}
	adj_list[src].push_front(std::make_pair(dst, weigth));
}

/*
template <typename T>
const void Graph<T>::dijkstra() //TODO sistemare tipo di ritorno
{
	std::cout << "I still do nothing! Implement me!";
}

template <typename T>
const void Graph<T>::bellmanFord() //TODO sistemare tipo di ritorno
{
	std::cout << "I still do nothing! Implement me!";
}

*/