template <typename T>
class Graph
{
public:
	Graph() {};		//costruttore di default

	void addVertex();
	void removeVertex();
	void addEdge();
	void removeEdge();

	static const void dijkstra();
	static const void bellmanFord();

private:
	
	/*by deisgn, il grafo è rappresentato da una collezione di liste, ergo un std::vector di std::forward_list.
	ogni indice del vector corrisponde ad un vertice, ogni elemento della list corrisponde ad un arco in partenza dal vertice [i] 
	ed in arrivo al contenuto della lista, rappresentata da una std::pair.

	L'idea è:

	idx vector	list[0]	 list[1]  list[2]..
	[0]			|2,3| -> |1,5| -> |3,-2|	//dal nodo 0 partono gli archi: 0->2 con costo 3, 0->1 con costo 5, 0->3 con costo -2.
	[1]			|3,2| -> |2,-3|				//dal nodo 1 partono gli archi: 1->3 con costo 2, 1->2 con costo -3
	...ecc ecc
	*/

	
	std::vector<std::forward_list<std::pair<int, T>>> adj_list;

	//ALTERNATIVA SEMPLIFICATA: uso una terna (tupla di 3) in modo da salvare sempre anche il nodo di partenza (ridondanza? Non lo so in automatico con l'index del vettore??)
	//std::vector<std::forward_list<std::tuple<int, int, T>>> adj_list;

	/*by deisgn, il grafo è rappresentato da una collezione di liste, ergo un std::vector di std::forward_list.
	ogni indice del vector corrisponde ad un vertice, ogni elemento della list corrisponde ad un arco in partenza dal vertice [i]
	ed in arrivo al contenuto della lista, rappresentata da una std::pair.

	L'idea è:

	idx vector	list[0]	 list[1]  list[2]..
	[0]			|0,2,3| -> |0,1,5| -> |0,3,-2|	//dal nodo 0 partono gli archi: 0->2 con costo 3, 0->1 con costo 5, 0->3 con costo -2.
	[1]			|1,3,2| -> |1,2,-3|				//dal nodo 1 partono gli archi: 1->3 con costo 2, 1->2 con costo -3
	...ecc ecc
	*/

};