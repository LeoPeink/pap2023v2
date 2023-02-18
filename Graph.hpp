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
		//iterator traits
		using iterator_category = std::forward_iterator_tag;
		using value_type = int;
		using reference = int&;
		using pointer = int*;
		using difference_type = std::ptrdiff_t;

		//convenience aliases
		using collection_data_type = std::vector<std::forward_list<std::pair<int, T>>>; //usiamo un alias per evitare di scrivere ogni volta il tipo completo

		vertex_iterator() = default;	//default constructible
		~vertex_iterator() = default;	//destructor

		vertex_iterator(const collection_data_type& adj_list, int pos = 0) :	//costruttore di copia che riceve un riferimento alla lista di adiacenza e un indice di partenza
			adj_list{ &adj_list },												//assegna i membri ai parametri
			pos{pos}
		{advance_to_valid();}													//e avanza al primo vertice valido

		//overload degli operatori
		vertex_iterator& operator++() {++pos; advance_to_valid(); return *this;}				//pre-incremento con avanzamento al prossimo vertice valido
		vertex_iterator operator++(int) {vertex_iterator old(*this); ++(*this); return old;}	//post-incremento con avanzamento al prossimo vertice valido
		bool operator==(const vertex_iterator& other) const {return pos == other.pos;}			//uguaglianza
		bool operator!=(const vertex_iterator& other) const {return !(*this == other);}			//disuguaglianza
		inline int operator*() const {return pos;}												//dereferenziazione
		//mancano gli operatori -> e * perche' non abbiamo un puntatore a un oggetto, ma un iteratore a un intero.
	
	private:
		void advance_to_valid()		//questa  funzione avanza al prossimo vertice valido, utile per non dover gestire a monte gli iteratori invalidi.
		{
			while (pos < adj_list->size() && (*adj_list)[pos].empty()) 
			{
				++pos;
			}
		}

		const collection_data_type* adj_list = nullptr;
		int pos = 0;
	};

	vertex_iterator begin() const {return vertex_iterator(adj_list);}

	vertex_iterator end() const {return vertex_iterator(adj_list, adj_list.size());}
	
	
	//edge iterator
	template <typename T>
	class edge_iterator : public std::iterator<std::forward_iterator_tag, std::pair<int, T>>
	{
	public:
		edge_iterator(typename std::vector<std::forward_list<std::pair<int, T>>>::iterator it_list, typename std::forward_list<std::pair<int, T>>::iterator it_edge)
			: it_list_(it_list), it_edge_(it_edge)
		{}

		edge_iterator& operator++()
		{
			++it_edge_;
			if (it_edge_ == it_list_->end())
			{
				++it_list_;
				if (it_list_ != end_list_)
					it_edge_ = it_list_->begin();
			}
			return *this;
		}

		bool operator==(const edge_iterator& other) const
		{
			return it_list_ == other.it_list_ && it_edge_ == other.it_edge_;
		}

		bool operator!=(const edge_iterator& other) const
		{
			return !(*this == other);
		}

		std::pair<int, T>& operator*()
		{
			return *it_edge_;
		}

		std::pair<int, T>* operator->()
		{
			return &(*it_edge_);
		}

	private:
		typename std::vector<std::forward_list<std::pair<int, T>>>::iterator it_list_;
		typename std::vector<std::forward_list<std::pair<int, T>>>::iterator end_list_;
		typename std::forward_list<std::pair<int, T>>::iterator it_edge_;

		friend class Graph<T>;
	};

	edge_iterator<T> begin(int v)
	{
		return edge_iterator<T>(adj_list.begin() + v, adj_list.at(v).begin());
	}

	edge_iterator<T> end(int v)
	{
		return edge_iterator<T>(adj_list.end(), adj_list.back().end());
	}


	/*
	static const void dijkstra();
	static const void bellmanFord();
	*/
	//getter&setter
	const std::vector<std::forward_list<std::pair<int, T>>> getAdjList() { return adj_list; }


private:

	std::vector<std::forward_list<std::pair<int, T>>> adj_list;
	//std::vector<std::forward_list<std::tuple<int, int, T>>> adj_list;
};