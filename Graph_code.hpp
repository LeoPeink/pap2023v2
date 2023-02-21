#include "Graph.hpp"
template <typename T>
void Graph<T>::addEdge(int src, int dst, T weigth)
{
    if(src < 0 || dst < 0)      //il programma non supporta nodi con identificativi negativi, perchè rappresentano indici di un vettore.
	{
		throw std::invalid_argument("Errore nell'inserimento di un arco: nodo negativo");
	}
    if (adj_list.size() <= src) //se sto inserendo un nodo che "sfora" il vector,
    {
        adj_list.resize(src + 1);   //aggiorna la dimensione
    }
    adj_list[src].push_front(std::make_pair(dst, weigth));  //ed inseriscilo. 
}

template<typename T>
inline const std::vector<std::forward_list<std::pair<int, T>>> Graph<T>::getAdjList()
{
	return adj_list;    //getter: rende visibile un attributo privato
}

template<typename T>
inline const int Graph<T>::getNumVertex()
{
    return static_cast<int>(adj_list.size()); //cast statico per risolvere il warning "size_t -> int", non dà problemi perchè size_t e int sono compatibili.
} 

template<typename T>
inline const T Graph<T>::getEdgeWeight(int src, int dst)
{
    if (src < 0 || dst < 0)      //il programma non supporta nodi con identificativi negativi, perchè rappresentano indici di un vettore.
    {
        throw std::invalid_argument("Errore nell'inserimento di un arco: nodo negativo");
    }
    for (auto it = begin(src); it != end(src); ++it)        //per estrarre il peso di un determinato arco (ad esempio per costruire l'albero dei cammini minimi)
	{                                                       //bisogna scorrere tutta la lista di adiacenza del nodo di partenza, e confrontare il nodo di arrivo
        auto edge = *it;                                    
		if (edge.first == dst)                              //con quello che si sta cercando. Se coincidono, 
        {
            return edge.second;                             //si estrae il peso.
        }
    }
    throw std::invalid_argument("Errore nell'estrazione del peso: arco non trovato"); //altrimenti, l'arco specificato non esiste.
}

template<typename T>
inline void Graph<T>::reset()
{
	adj_list.clear();   //funzione util per resettare il grafo, in modo da poterlo riutilizzare.
}

template<typename T>
inline const Graph<T> Graph<T>::dijkstra(Graph& g, int src)
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
        
        if (visited.size() <= u){visited.resize(u + 1, false);} //(controllo che le strutture dati di appoggio abbiano dimensione sufficiente)

        if (visited[u] == false)    // Se il nodo corrente non e' gia' stato visitato.
        {
            visited[u] = true;      //lo imposto come visitato,
            auto it = g.begin(u);
            for (auto it = g.begin(u); it != g.end(u); ++it)    // e per ogni arco uscente dal vertice "u",
            {
                auto edge = *it;        // prendo il vertice di arrivo e il peso dell'arco:
                int v = edge.first;     //( "v" rappresenta il vertice di arrivo )
                T w = edge.second;      //( "w" il peso dell'arco )

				if (prec.size() <= v || distances.size() <= v || visited.size() <= v) //(controllo che le strutture dati di appoggio abbiano dimensione sufficiente)
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
inline const Graph<T> Graph<T>::bellmanFord(Graph& g, int src)
{
    if (src < 0 || src >= g.getNumVertex()) // Verifica che il nodo di partenza sia valido
    {
        throw std::invalid_argument("Nodo di partenza non valido");
    }


    std::vector<T> distances(g.getNumVertex()+1, std::numeric_limits<T>::max());  //vettore con le distanze da src a tutti gli altri
    std::vector<int> prec(g.getNumVertex()+1, -1);                                //vettore con i precedenti, inizializzato a -1
    distances[src] = 0;                                                           //la distanza src->src e' 0

    for (int i = 1; i < g.getNumVertex(); i++)        //per v-1 volte
    {
        for (auto it_v = g.begin(); it_v != g.end(); ++it_v) //per ogni vertice
        {
            int u = *it_v;                                              //"u" rappresenta il vertice di partenza

            for (auto it_e = g.begin(u); it_e != g.end(u); ++it_e)  //per ogni arco in partenza da "u",
            {
                auto edge = *it_e;          // prendo il vertice di arrivo e il peso dell'arco:
                int v = edge.first;         //( "v" rappresenta il vertice di arrivo )
                T weigth = edge.second;      //( "w" il peso dell'arco )
                
				if (prec.size() <= v || distances.size() <= v)  //(controllo che le strutture dati di appoggio abbiano dimensione sufficiente)
                {
                    distances.resize(v + 1, std::numeric_limits<T>::max());
                    prec.resize(v + 1, -1);
                }
                
                if (distances[u] != std::numeric_limits<T>::max() && distances[u] + weigth < distances[v]) //se il percorso in analisi conviene rispetto al precedente,
                {
                    distances[v] = distances[u] + weigth;                                                  //aggiorna le distanze
                    prec[v] = u;                                                                           //ed imposta il nuovo precedente.
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
            }
        }
    }
    //costruisci un sottografo di "g" con solo i cammini minimi
    return buildShortestPathTree(g, prec, distances);
}

template<typename T>
const Graph<T> Graph<T>::buildShortestPathTree(Graph<T>& g, std::vector<int>& prev, std::vector<T>& dist)
{
    Graph<T> tree;  //NB: questo metodo è privato e viene richiamato soltanto in "dijkstra" e "bellmanFord", ergo si presuppone che gli array in input siano validi.

    // Scandisce i nodi del grafo e inserisce gli archi dell'albero
    for (int i = 0; i < prev.size(); i++)                               //ciclo con la dimensione dell'array di precedenti perchè la sua dimensione coincide sempre con la quantità di vertici nell'albero di percorsi minimi
    {
        if (prev[i] != -1)          // Se il nodo corrente non e' la radice dell'albero (la quale non ha predecessori)
        {
            int prev_node = prev[i];                    //prev_node è il nodo di partenza
			T weight = g.getEdgeWeight(prev_node, i);   //weigth è il peso dell'arco
            tree.addEdge(prev_node, i, weight);         //aggiungi all'albero l'arco.
        }
    }
    return tree;
}

