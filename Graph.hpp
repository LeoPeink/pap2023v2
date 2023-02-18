#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <queue>
#include <forward_list>

template <typename T>
class Graph
{
public:

	Graph() {};		//costruttore di default
	~Graph() = default;	//distruttore di default

	void addEdge(int src, int dst, T weigth);

	//iteratore per i vertici
	class VertexIterator
	{
	public:
		//iterator traits
		using iterator_category = std::forward_iterator_tag;
		using value_type = int;
		using reference = int&;
		using pointer = int*;
		using difference_type = std::ptrdiff_t;
		//convenience aliases
		using collection_data_type = std::vector<std::forward_list<std::pair<int, T>>>; //usiamo un alias per evitare di scrivere ogni volta il tipo completo

		VertexIterator() = default;	//default constructible
		~VertexIterator() = default;	//destructor

		VertexIterator(const collection_data_type& adj_list, int pos = 0) :	//costruttore di copia che riceve un riferimento alla lista di adiacenza e un indice di partenza
			adj_list{ &adj_list },												//assegna i membri ai parametri
			pos{ pos }
		{
			advance_to_valid();
		}													//e avanza al primo vertice valido

		//overload degli operatori
		VertexIterator& operator++() { ++pos; advance_to_valid(); return *this; }				//pre-incremento con avanzamento al prossimo vertice valido
		VertexIterator operator++(int) { VertexIterator old(*this); ++(*this); return old; }	//post-incremento con avanzamento al prossimo vertice valido
		bool operator==(const VertexIterator& other) const { return pos == other.pos; }			//uguaglianza
		bool operator!=(const VertexIterator& other) const { return !(*this == other); }			//disuguaglianza
		inline int operator*() const { return pos; }												//dereferenziazione
		//mancano gli operatori -> e * perche' non abbiamo un puntatore a un oggetto, ma un iteratore a un intero.

	private:
		void advance_to_valid()		//questa funzione avanza al prossimo vertice valido, utile per non dover gestire a monte gli iteratori invalidi.
		{
			while (pos < adj_list->size() && (*adj_list)[pos].empty())
			{
				++pos;
			}
		}

		const collection_data_type* adj_list = nullptr;
		int pos = 0;
	};
	VertexIterator begin() const { return VertexIterator(adj_list); }
	VertexIterator end() const { return VertexIterator(adj_list, (int)adj_list.size()); } //TODO int casting o sistemare tipo


	//edge iterator
	class EdgeIterator {

		//iterator traits
		using difference_type = std::ptrdiff_t;
		using value_type = std::pair<int, T>;
		using pointer = std::pair<int, T>*;
		using reference = std::pair<int, T>&;
		using iterator_category = std::forward_iterator_tag;
		//convenience alias
		using AdjListIterator = typename std::forward_list<std::pair<int, T>>::iterator; //usiamo un alias per evitare di scrivere ogni volta il tipo completo

	public:
		EdgeIterator(AdjListIterator edge_it) : edge_it(edge_it) {}							// Costruttore di copia
		reference operator*() { return *edge_it; }												// Operatore di dereferenziazione, restituisce l'arco corrente
		EdgeIterator& operator++() { ++edge_it; return *this; }									// Operatore di incremento prefisso, sposta l'iteratore all'arco successivo
		EdgeIterator operator++(int) { EdgeIterator old(*this); ++(*this); return old; }		// Operatore di incremento postfisso, sposta l'iteratore all'arco successivo
		bool operator==(const EdgeIterator& other) const { return edge_it == other.edge_it; }	// Operatore di uguaglianza, confronta gli iteratori correnti
		bool operator!=(const EdgeIterator& other) const { return !(*this == other); } 			// Operatore di disuguaglianza, confronta gli iteratori correnti

	private:
		AdjListIterator edge_it;
		friend class Graph<T>;
	};
	EdgeIterator begin(int v) { return EdgeIterator(adj_list[v].begin()); }
	EdgeIterator end(int v) { return EdgeIterator(adj_list[v].end()); }



	static const Graph<T> dijkstra(Graph g, int src);	
	static const Graph<T> bellmanFord(Graph g, int src);


	const std::vector<std::forward_list<std::pair<int, T>>> getAdjList() { return adj_list; }
	const int getNumVertex() { return static_cast<int>(adj_list.size()); } //cast statico per aggirare il warning "size_t -> int", non d� problemi perch� size_t e int sono compatibili.
	
	const T getEdgeWeight(int src, int dst) 
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
		return -1; //TODO gestire errore? Si potrebbe mai verificare?
	}

	void reset(){adj_list.clear(); }

private:
	std::vector<std::forward_list<std::pair<int, T>>> adj_list;
	//std::vector<std::forward_list<std::tuple<int, int, T>>> adj_list;
	static Graph<T> build_shortest_path_tree(Graph<T> g, std::vector<int>& prev, std::vector<T>& dist);
};

#include "Graph_code.hpp"
#endif
