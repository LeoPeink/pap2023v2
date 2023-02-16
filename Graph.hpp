template <typename T>
class Graph
{
public:
	//costruttori
	Graph() {};		//costruttore di default
	
	//metodi
	//void removeVertex(); rimossa per consistenza dei dati
	void addEdge(int src, int dst, T weigth);
	//void removeEdge(); rimossa per consistenza dei dati.


	class vertex_iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		//using value = int;
		using value = std::forward_list<std::pair<int, T>>;
		using pointer = value*;
		using reference = value&;

		vertex_iterator() : ptr{ nullptr }, index{ 0 } {} //costruttore originale
		//costruttore che riceve un puntatore e imposta a 0 l'indice
		//vertex_iterator(pointer ptr) : ptr{ ptr }, index{ 0 } {} //prova finale
		//vertex_iterator(pointer ptr) : ptr{ ptr } {} //orig
		//vertex_iterator(pointer ptr, size_t index) : ptr{ ptr }, index{ index } {} //mod
		//vertex_iterator(pointer lst, size_t index) : ptr{ ptr } {}

		vertex_iterator& operator++() { ++ptr; ++index; return *this; } //mod
		//vertex_iterator& operator++() { ++ptr; return *this; } //orig
		 
		vertex_iterator operator++(int) { vertex_iterator tmp{ *this }; ++ptr; ++index; return tmp; } //mod
		//vertex_iterator operator++(int) { vertex_iterator tmp{ *this }; ++ptr; return tmp; } //orig

		reference operator*() { return *ptr; }
		pointer operator->() { return ptr; }

		bool operator==(const vertex_iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const vertex_iterator& other) const { return ptr != other.ptr; }

		size_t get_index() const { return index; }

	private:
		pointer ptr;
		size_t index; //mod
		vertex_iterator(pointer ptr) : ptr{ ptr }, index{ 0 } {}	//costruttore privato per creare un iteratore a partire da un puntatore: privato per evitare mismatch di tipi tra il container e l'iteratore

		friend class Graph<T>;
	};

	class edge_iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;	//iterator_category: è un forward
		using difference_type = std::ptrdiff_t;					//la differenza tra puntatori è un ptrdiff_type 
		using value = std::pair<int, T>;										//il tipo di dato che contiene l'iteratore
		using pointer = value*;									//il tipo di dato puntato dall'iteratore
		using reference = value&;								//il tipo riferimento puntato dall'iteratore

		edge_iterator() : ptr{ nullptr } {};												//costruttore di default
		//iterator(const iterator& it) : it{ it.it } {};									//costruttore di copia: inutile perchè già implicitamente implementato 
		//iterator& operator=(const iterator& it) { this->it = it.it; return *this; }		//operatore di copia  : inutile perchè già implicitamente implementato
		edge_iterator& operator++() { ++ptr; return *this; }								//operatore di incremento prefisso
		edge_iterator operator++(int) { edge_iterator tmp{ *this }; ++ptr; return tmp; }//operatore di incemento postfisso
		inline reference operator*() { return *ptr; }										//operatore di dereferenziazione
		inline pointer operator->() { return ptr; }											//operatore puntatore			
		inline bool operator==(const edge_iterator& it) { return ptr == it.ptr; }			//operatore uguaglianza
		inline bool operator!=(const edge_iterator& it) { return ptr != it.ptr; }			//operatore disuguaglianza


	private:
		edge_iterator(pointer ptr) : ptr{ ptr } {};		//costruttore privato per creare un iteratore a partire da un puntatore: privato per evitare mismatch di tipi tra il container e l'iteratore

		pointer ptr; //puntatore all'elemento associato all'iteratore

		friend class Graph<T>;	//permette a Graph di accedere ai membri privati di iterator
	};

	inline vertex_iterator v_begin() { return vertex_iterator{ &adj_list[0], 0 }; }	//ritorna un iteratore al primo elemento del vettore di vertici
	inline vertex_iterator v_end() { return vertex_iterator{ &adj_list[adj_list.size() - 1] + 1 }; }	//ritorna un iteratore all'ultimo elemento del vettore di v
	inline edge_iterator e_begin() { return  edge_iterator{ adj_list[i].begin()}; }	//ritorna un iteratore
	inline edge_iterator e_end() { return edge_iterator{ adj_list[i].end() }; }	//ritorna un iteratore

	static const void dijkstra();
	static const void bellmanFord();

	//getter&setter
	const std::vector<std::forward_list<std::pair<int, T>>> getAdjList(){return adj_list;}


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