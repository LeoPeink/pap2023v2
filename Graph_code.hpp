#include "Graph.hpp"
template <typename T>
void Graph<T>::addEdge(int src, int dst, T weigth)
{
    if(src < 0 || dst < 0)
	{
		throw std::invalid_argument("Errore nell'inserimento di un arco: nodo negativo");
	}
    if (adj_list.size() <= src)
    {
        adj_list.resize(src + 1);
    }
    adj_list[src].push_front(std::make_pair(dst, weigth));
}


template<typename T>
inline const std::vector<std::forward_list<std::pair<int, T>>> Graph<T>::getAdjList()
{
    return adj_list;
}

template<typename T>
inline const int Graph<T>::getNumVertex()
{
    return static_cast<int>(adj_list.size()); //cast statico per aggirare il warning "size_t -> int", non dà problemi perchè size_t e int sono compatibili.
} 

template<typename T>
inline const T Graph<T>::getEdgeWeight(int src, int dst)
{
    //find the weight of the edge from src to dst
    for (auto it = begin(src); it != end(src); ++it)
    {
        auto edge = *it;
        if (edge.first == dst)
        {
            return edge.second;
        }
    }
    throw std::invalid_argument("Errore nell'estrazione del peso");
}

template<typename T>
inline void Graph<T>::reset()
{
    adj_list.clear();
}

template<typename T>
inline const Graph<T> Graph<T>::dijkstra(Graph g, int src)
{
    if (src < 0 || src >= g.getNumVertex()) // Verifica che il nodo di partenza sia valido
    {
        throw std::invalid_argument("Nodo di partenza non valido");
    }

    //INIZIALIZZAZIONE:

    //strutture dati di supporto:    
    std::vector<T> distances(g.getNumVertex(), std::numeric_limits<T>::max());  //vettore con le distanze da src a tutti gli altri
    std::vector<bool> visited(g.getNumVertex(), false);                         //vettore con i nodi visitati
    std::vector<int> prec(g.getNumVertex(), -1);                                //vettore con i precedenti, inizializzato a -1
    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> pq; //priority queue per il minimo

    distances[src] = 0;                 //la distanza src->src e' 0
    pq.push(std::make_pair(0, src));    //metto in coda il primo nodo con distanza 0

    //ALGORITMO:

    while (!pq.empty())             //finchè la coda non è vuota,
    {
        int u = pq.top().second;    // Prende il vertice con la minima distanza dalla coda con priorita',
        pq.pop();                   // lo rimuove dalla coda.
        
        if (visited.size() <= u){visited.resize(u + 1, false);} //errore vector out of range

        if (visited[u] == false)    // Se il nodo corrente non e' gia' stato visitato.
        {
            visited[u] = true;      //lo imposto come visitato,
            auto it = g.begin(u);
            for (auto it = g.begin(u); it != g.end(u); ++it)    // e per ogni arco uscente dal vertice "u",
            {
                auto edge = *it;        // prendo il vertice di arrivo e il peso dell'arco:
                int v = edge.first;     //( "v" rappresenta il vertice di arrivo )
                T w = edge.second;      //( "w" il peso dell'arco )

                //(check su dimensione di prec)
                if (prec.size() <= v || distances.size() <= v || visited.size() <= v)
                {
                    distances.resize(v + 1, std::numeric_limits<T>::max());
                    prec.resize(v + 1, -1); 
                    visited.resize(v + 1, false);
                }
                if (w < 0) { throw std::runtime_error("Grafo con pesi negativi"); } //controllo sulla validità del grafo in input

                if (distances[v] > distances[u] + w)    // Se il cammino in analisi conviene rispetto all'ultimo cammino trovato,
                {
                    distances[v] = distances[u] + w;            //aggiorno la distanza da src a v,
                    prec[v] = u;                                //e imposto u come predecessore di v.
                    pq.push(std::make_pair(distances[v], v));   //Inoltre, segno v come possibile prossimo nodo da visitare
                }
            }
        }
    }

    //costruisci un Graph con i cammini minimi
    return buildShortestPathTree(g, prec, distances);
}

template<typename T>
inline const Graph<T> Graph<T>::bellmanFord(Graph g, int src)
{
    if (src < 0 || src >= g.getNumVertex()) // Verifica che il nodo di partenza sia valido
    {
        throw std::invalid_argument("Nodo di partenza non valido");
    }


    std::vector<T> distances(g.getNumVertex()+1, std::numeric_limits<T>::max());  //vettore con le distanze da src a tutti gli altri
    std::vector<int> prec(g.getNumVertex()+1, -1);                                //vettore con i precedenti, inizializzato a -1
    distances[src] = 0;                                                            //la distanza src->src e' 0

    for (int i = 1; i < g.getNumVertex(); i++)        //per v-1 volte
    {
        for (auto it_v = g.begin(); it_v != g.end(); ++it_v) //per ogni vertice
        {
            int u = *it_v; //vertice di partenza

            for (auto it_e = g.begin(u); it_e != g.end(u); ++it_e)
            { //estrai gli archi
                auto edge = *it_e;        // prendo il vertice di arrivo e il peso dell'arco:
                int v = edge.first;     //( "v" rappresenta il vertice di arrivo )
                T weigth = edge.second;      //( "w" il peso dell'arco )
                
                if (prec.size() <= v || distances.size() <= v)
                {
                    distances.resize(v + 1, std::numeric_limits<T>::max());
                    prec.resize(v + 1, -1);
                }
                
                if (distances[u] != std::numeric_limits<T>::max() && distances[u] + weigth < distances[v])//confronto per relax degli archi
                {
                    distances[v] = distances[u] + weigth;
                    prec[v] = u;
                }
            }
        }
    }

    //controllo per cicli negativi
    for (auto it_v = g.begin(); it_v != g.end(); ++it_v) //per ogni vertice
    {
        int u = *it_v;
        //vertice di partenza        
        for (auto it_e = g.begin(u); it_e != g.end(u); ++it_e)  //estrai gli archi
        {
            auto edge = *it_e;          // prendo il vertice di arrivo e il peso dell'arco:
            int v = edge.first;         //( "v" rappresenta il vertice di arrivo )
            T weight = edge.second;          //( "w" il peso dell'arco )
            if (distances[u] != std::numeric_limits<T>::max() && distances[u] + weight < distances[v])
            { //se è possibile ridurre ancora il cammino minimo allora esiste un ciclo negativo
                throw std::runtime_error("Ciclo di peso negativo trovato.");
                //return build_shortest_path_tree(g, prec, distances);
            }
        }
    }
    //costruisci un Graph con i cammini minimi
    return buildShortestPathTree(g, prec, distances);
}

template<typename T>
const Graph<T> Graph<T>::buildShortestPathTree(Graph<T> g, std::vector<int>& prev, std::vector<T>& dist)
{
    Graph<T> tree;

    // Scandisce i nodi del grafo e inserisce gli archi dell'albero
    /*
    for (int i = 0; i < prev.size(); i++)
    {
        // Se il nodo corrente e' la radice dell'albero, non ha predecessori
        if (prev[i] != -1)
        {
            // Aggiunge l'arco del predecessore al nodo corrente
            int prev_node = prev[i];
            T weight = g.getEdgeWeight(prev_node, i);
            tree.addEdge(prev_node, i, weight);
        }
    }
    */
    for (auto it = g.begin(); it != g.end(); ++it)
    {
        // Se il nodo corrente e' la radice dell'albero, non ha predecessori
        if (prev[*it] != -1)
        {
            // Aggiunge l'arco del predecessore al nodo corrente
            int prev_node = prev[*it];
            T weight = g.getEdgeWeight(prev_node, *it);
            tree.addEdge(prev_node, *it, weight);
        }
    }
    return tree;
}

