#include "Graph.hpp"
#include <queue>
#include <unordered_set>


/*
template <typename T>
void Graph<T>::removeVertex()	//PROBLEMA: rimuovendo un vertice gli altri scalano, perdendo i nomi dei grafi.
{
	std::cout << "I still do nothing! Implement me!";
}
*/

template <typename T>
void Graph<T>::addEdge(int src, int dst, T weigth)
{
	if (adj_list.size() <= src)
	{
		adj_list.resize(src + 1);
	}
	adj_list[src].push_front(std::make_pair(dst, weigth));
}

template<typename T>
inline const std::vector<T> Graph<T>::dijkstra(Graph g, int src)
{
    std::vector<std::forward_list<std::pair<int, T>>> graph = g.getAdjList();
    //grafo passato come vettore di liste linkate
    int n = graph.size();

    if (src < 0 || src >= n)
    {
        throw std::invalid_argument("Nodo di partenza non valido");  // Verifica che il nodo di partenza sia valido
    }

    std::vector<T> distances(n, std::numeric_limits<T>::max());
    distances[src] = 0;

    //create a priority queue
    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> pq;
    pq.push(std::make_pair(0, src));
    //coda di priorità che riceve in input una coppia(T, int), costruisce la coda un vettore di pesi(T) e indice del vertice(int) e ordina direttamente in modo crescente in base alla         distanza utilizzando la funzione greater

    std::unordered_set<int> visited; //unordered_set ha una complessità minore rispetto a vector o list, controllo dell'appartenenza di un elemento all'insieme in tempo costante.
    int iteration_count = 0;

    while (!pq.empty())
    {
        std::pair<T, int> top = pq.top();  // Prende il vertice con la minima distanza dalla coda con priorità
        pq.pop();
        int u = top.second;                // "u" è il nodo di partenza

        // Controlla se il nodo corrente è già stato visitato
        if (visited.find(u) != visited.end())
        { //find restituisce un iteratore all'elemento trovato, oppure l'iteratore di fine dell'insieme se l'elemento non è presente
            continue;
        }
        visited.insert(u);

        for (auto it = graph[u].begin(); it != graph[u].end(); ++it)
        {  //per ogni arco uscente dal vertice
            int v = it->first;  //vertice di arrivo
            T w = it->second;  //peso dell'arco

            if (distances[v] > distances[u] + w)
            {  // Per ogni nodo v adiacente a u, aggiorna la distanza se coveniente
                distances[v] = distances[u] + w;
                pq.push(std::make_pair(distances[v], v));
            }
        }

        iteration_count++; // aumento il contatore ad ogni iterazione

        if (iteration_count > n)
        { // se supero il numero massimo di iterazioni, significa che c'è un ciclo di peso negativo
            throw std::runtime_error("Ciclo di peso negativo trovato");
        }
    }

    return distances;
}


/*
template <typename T>
const void Graph<T>::bellmanFord() //TODO sistemare tipo di ritorno
{
	std::cout << "I still do nothing! Implement me!";
}

*/