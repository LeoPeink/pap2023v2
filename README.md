<h1>pap2023v2</h1>

**Programmazione Avanzata e Parallela 2023, 2° tentativo.<br> Progetto di Programmazione Avanzata e Parallela, UniTS, AIDA, 2023: realizzazione di una classe template per la creazione di grafi ed implementazione degli algoritmi di ottimizzazione per la ricerca del percorso di costo minimo "Dijkstra" e "Bellman-Ford".**

*Autori: Leo Peinkhofer, Lorenzo Di Bernardo*

**<h2>Documentazione:</h2>**<ul> <li>**Graph** -> Includendo Graph.hpp si includono automaticamente le librerie: *"queue", "vector", "forward_list", "pair", "limits", "algorithm", "iterator"</li>*

<li>Graph è una classe template che accetta qualsiasi tipo primitivo come T. T rappresenta il tipo di pesi degli archi del grafo.</li></ul>

**<h2>Attributi Graph non espone attributi pubblici:</h2>**

<ul><li><code>(private) std::vector<std::forward_list<std::pair<int, T>>> adj_list;</code>
<ul><li>È la lista di adiacenza che contiene tutti gli archi che compongono il grafo.</li> <li>Ogni vertice è univocamente identificato dall'indice del "std::vector" in cui si trova.</li> <li>Ogni "forward_list" rappresenta gli archi in partenza dal nodo std::vector[n] (private) std::string name</li></ul></ul>
  <ul><li><code>(private) std::unordered_map<T, std::unordered_map<T, int>> edges;</code></li></ul>
  <ul><li><code>(private) std::vector getVertices():</code> Restituisce il vector di vertici</li></ul>
  <ul><li><code>(private) std::unordered_map<T, std::unordered_map<T, int>> getEdges():</code> Restituisce la mappa di mappe contenente archi e pesi</li></ul>

**<h2>Metodi pubblici:**</h2>

  <ul>
    <li><code>void addEdge(int src, int dst, T weight):</code> Aggiunge un arco da srt a dst di peso weight alla adj_list.</li>
    <li><code>VertexIterator begin():</code> Ritorna un iteratore al primo elemento del vettore</li>
    <li><code>VertexIterator end():</code> Ritorna un iteratore all'ultimo elemento del vettore</li>
    <li><code>EdgeIterator begin(int v):</code> Ritorna un iteratore al primo elemento della lista di adiacenza in posizione [v] del vettore</li>
    <li><code>EdgeIterator end(int v):</code> Ritorna un iteratore dopo l'ultimo elemento della lista in posizione [v] del vettore </li>
    </ul>

**<h2>Metodi della classe:**</h2><ul><li> 
`std::unordered_map<T, int>> dijkstra(Graph g, T src):` 
<ul><li>Esegue l'algoritmo di Dijkstra sul grafo g specificato, a partire dal nodo src.</li> 
<li>Ritorna la lista delle distanze come mappa di coppie "nodo di arrivo" : costo di arrivo.</ul></ul></li><ul><li>
  
  `std::unordered_map<T, int>> bellmanFord(Graph g, T src):`
 
<ul><li>Esegue l'algoritmo di Bellman-Ford sul grafo g specificato, a partire dal nodo src.</li><li>Ritorna la lista delle distanze come mappa di coppie "nodo di arrivo" : costo di arrivo.</li></ul></ul>

**<h2>Varie:</h2>**<ul><li> 
  <code>errorMessages.h:</code> Questo file contiene vari messaggi di errore che vengono usati per gestire a livello di interfaccia utente alcune eccezioni o casi limite.</li>
  <li><code>Main.cpp:</code> Questo file sorgente contiene un metodo main() con un menu pre-configurato, al fine di verificare facilmente il funzionamento della libreria tramite CLI.</li></ul>

**<h2>Demo images**</h2><ul><li> 
  La cartella contiene la rappresentazione grafica dei grafi pre-impostati nel menu per facilitare il test della libreria.</ul></li>
