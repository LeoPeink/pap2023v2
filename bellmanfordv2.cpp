#include <limits>
#include <forward_list>
#include <vector>
#include <stdexcept>


template<typename T>
void bellman_ford(const std::vector<std::forward_list<std::pair<int, T>>>& graph, int start, std::vector<T>& distances) {
    int n = graph.size();
    distances.assign(n, std::numeric_limits<T>::max()); //inizializza le distanze a infinito
    distances[start] = 0; //tranne la sorgente

    for (int i = 1; i < n; i++) {  //per v-1 volte
        for (auto it_u = graph.begin(); it_u != graph.end(); ++it_u) {  //per ogni vertice
            int u = std::distance(graph.begin(), it_u);
            for (auto it_edge = it_u->begin(); it_edge != it_u->end(); ++it_edge) { //estrai gli archi
                int v = it_edge->first; //vertice di arrivo
                T weight = it_edge->second; //peso dell'arco
                if (distances[u] != std::numeric_limits<T>::max() && distances[u] + weight < distances[v]) { //confronto per relax degli archi
                    distances[v] = distances[u] + weight;
                }
            }
        }
    }

    //controllo per cicli negativi
    for (auto it_u = graph.begin(); it_u != graph.end(); ++it_u) { //ancora una volta cicla tutti i vertici
        int u = std::distance(graph.begin(), it_u);
        for (auto it_edge = it_u->begin(); it_edge != it_u->end(); ++it_edge) { //per ognuno considera i suoi archi
            int v = it_edge->first; //vertice di arrivo
            T weight = it_edge->second; //peso dell'arco
            if (distances[u] != std::numeric_limits<T>::max() && distances[u] + weight < distances[v]) { //se è possibile ridurre ancora il cammino minimo allora esiste un ciclo negativo
                throw std::runtime_error("Ciclo di peso negativo trovato");
            }
        }
    }
}