#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>
#include <climits>

using namespace std;

template <typename T>
vector<T> dijkstra(vector<forward_list<pair<int, T>>>& graph, int start) { //grafo passato come vettore di liste linkate
    int n = graph.size();

    // Inizializzazione delle distanze
    vector<T> dist(n, numeric_limits<T>::max()); //inizializzo il vettore delle distanze a infinito
    dist[start] = 0; //distanza per la sorgente a zero

    // Coda con priorità degli elementi da esaminare
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq; 
    //coda di priorità che riceve in input una coppia(T, int), costruisce la coda un vettore di pesi(T) e indice del vertice(int) e ordina direttamente in modo crescente in base alla distanza utilizzando la funzione greater
    pq.push(make_pair(0, start)); //viene inserito nella coda con priorità il nodo di partenza start con distanza 0

    while (!pq.empty()) {
        // Prende il nodo con la minima distanza dalla coda con priorità
        pair<T, int> top = pq.top();
        pq.pop();
        int u = top.second;

        // Se abbiamo già trovato il percorso più breve verso u, passiamo al prossimo nodo
        if (top.first > dist[u]) {
            continue;   //todo modifica
        }

        // Per ogni nodo v adiacente a u, aggiorna la distanza se possibile
        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;
            T w = neighbor.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}