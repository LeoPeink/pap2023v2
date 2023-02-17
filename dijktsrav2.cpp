#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>
#include <limits>
#include <unordered_set>


//complessità (V + E log V)
template <typename T>
std::vector<T> dijkstra(std::vector<std::forward_list<std::pair<int, T>>>& graph, int start) { //grafo passato come vettore di liste linkate
    int n = graph.size();
   
    if (start < 0 || start >= n) {
        throw std::invalid_argument("Nodo di partenza non valido");  // Verifica che il nodo di partenza sia valido
    }

    std::vector<T> distances(n, std::numeric_limits<T>::max());
    distances[start] = 0;

    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> pq;
    pq.push(std::make_pair(0, start));
    //coda di priorità che riceve in input una coppia(T, int), costruisce la coda un vettore di pesi(T) e indice del vertice(int) e ordina direttamente in modo crescente in base alla         distanza utilizzando la funzione greater

    std::unordered_set<int> visited; //unordered_set ha una complessità minore rispetto a vector o list, controllo dell'appartenenza di un elemento all'insieme in tempo costante.
    int iteration_count = 0;
    
    while (!pq.empty()) {
        std::pair<T, int> top = pq.top();  // Prende il vertice con la minima distanza dalla coda con priorità
        pq.pop();
        int u = top.second;

        // Controlla se il nodo corrente è già stato visitato
        if (visited.find(u) != visited.end()) { //find restituisce un iteratore all'elemento trovato, oppure l'iteratore di fine dell'insieme se l'elemento non è presente
        continue;
        }
        visited.insert(u);

        for (auto it = graph[u].begin(); it != graph[u].end(); ++it) {  //per ogni arco uscente dal vertice
            int v = it->first;  //vertice di arrivo
            T w = it->second;  //peso dell'arco

            if (distances[v] > distances[u] + w) {  // Per ogni nodo v adiacente a u, aggiorna la distanza se coveniente
                distances[v] = distances[u] + w;
                pq.push(std::make_pair(distances[v], v));
            }
        }

        iteration_count++; // aumento il contatore ad ogni iterazione

        if (iteration_count > n) { // se supero il numero massimo di iterazioni, significa che c'è un ciclo di peso negativo
            throw std::runtime_error("Ciclo di peso negativo trovato");
        }
    }
    

    return distances;
}