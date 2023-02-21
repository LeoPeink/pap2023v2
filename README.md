<h1>pap2023v2</h1>

**Programmazione Avanzata e Parallela 2023, 2° tentativo.<br> Progetto di Programmazione Avanzata e Parallela, UniTS, AIDA, 2023: realizzazione di una classe template per la creazione di grafi ed implementazione degli algoritmi di ottimizzazione per la ricerca del percorso di costo minimo "Dijkstra" e "Bellman-Ford".**

*Autori: Leo Peinkhofer, Lorenzo Di Bernardo*

**<h2>Documentazione:</h2>**<ul> <li>**Graph** -> Includendo Graph.hpp si includono automaticamente le librerie: *"queue", "vector", "forward_list", "pair", "limits", "algorithm", "iterator"</li>*

<li>Graph è una classe template che accetta qualsiasi tipo primitivo come T. T rappresenta il tipo di pesi degli archi del grafo.</li></ul>

**<h2>Attributi Graph non espone attributi pubblici:</h2>**

<ul><li><code>'(private) std::vector<std::forward_list<std::pair<int, T>>> adj_list;'</code>
<ul><li>È la lista di adiacenza che contiene tutti gli archi che compongono il grafo.</li> <li>Ogni vertice è univocamente identificato dall'indice del "std::vector" in cui si trova.</li> <li>Ogni "forward_list" rappresenta gli archi in partenza dal nodo std::vector[n] (private) std::string name</li></ul></ul>

  <ul><li><code>(private) std::vector < std::forward_list < std::pair < int, T > > > getAdjList(): </code> Restituisce il vector di liste di archi.</li></ul>
  <ul><li><code>(private) Graph<T> buildShortestPathTree(Graph<T> g, std::vector<int>& prev, std::vector<T>& dist);</code> Restituisce, a partire da un vettore con le distanze ed un vettore con i precedenti di ogni nodo, l'albero dei cammini minimi. Metodo privato richiamato soltanto in "dijkstra" e "bellmanFord".</li></ul>
**<h2>Metodi pubblici:**</h2>

  <ul>
    <li><code>void addEdge(int src, int dst, T weight):</code> Aggiunge un arco da srt a dst di peso weight alla adj_list.</li>
    <li><code>VertexIterator begin():</code> Restituisce un iteratore al primo elemento del vettore</li>
    <li><code>VertexIterator end():</code> Restituisce un iteratore all'ultimo elemento del vettore</li>
    <li><code>EdgeIterator begin(int v):</code> Restituisce un iteratore al primo elemento della lista di adiacenza in posizione [v] del vettore</li>
    <li><code>EdgeIterator end(int v):</code> Restituisce un iteratore dopo l'ultimo elemento della lista in posizione [v] del vettore </li>
    <li><code>int getNumVertex():</code> Restituisce la quantità di vertici da cui parte almeno un arco.</li>
    <li><code>T getEdgeWeight(int src, int dst)</code> Restituisce il peso dell'arco da "src" a "dst" (se esistente)</li>
  </ul>

**<h2>Metodi della classe:**</h2><ul><li> 
`Graph<T> dijkstra(Graph g, int src):` 
<ul><li>Esegue l'algoritmo di Dijkstra sul grafo g specificato, a partire dal nodo src.</li> 
<li>Restituisce un sottografo di "g" avente soltanto i percorsi minimi da "src" a tutti i nodi da esso raggiungibili.</ul></ul></li><ul><li>
  
 `Graph<T> bellmanFord(Graph g, int src):` 
<ul><li>Esegue l'algoritmo di Bellman-Ford sul grafo g specificato, a partire dal nodo src.</li> 
<li>Restituisce un sottografo di "g" avente soltanto i percorsi minimi da "src" a tutti i nodi da esso raggiungibili.</ul></ul></li><ul><li>

**<h2>Varie:</h2>**<ul>
  <li><code>Main.cpp:</code> Questo file sorgente contiene, oltre ad un main(), un metodo menu() pre-configurato, al fine di verificare facilmente il funzionamento della libreria tramite CLI.</li></ul>

**<h2>Demo images**</h2><ul><li> 
  "Demo images.jpg" contiene la rappresentazione grafica dei grafi pre-impostati nel menu per facilitare il test della libreria.</ul></li>
