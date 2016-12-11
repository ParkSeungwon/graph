#pragma once
#include<climits>
#include<cassert>
#include<fstream>
#include<iostream>
#include<map>
#include<vector>
#include<stack>
#define min(a, b) a < b ? a : b
extern std::ostream& operator<<(std::ostream& o, const std::array<int, 5>& r);

template <typename T> class Vertex;
template<typename T> class Edge
{
public:
	int weight = 0;
	int v = 0;
	struct Vertex<T>* vertex = nullptr;
	struct Edge<T>* edge = nullptr;
};

template<typename T> class Vertex
{
public:
	T data;
	int v = 0;
	struct Edge<T>* edge = nullptr;
	struct Vertex<T>* vertex = nullptr;
};

template<typename T> class Graph
{
public:
	virtual ~Graph() {
		gfree(root);
		root = nullptr;
	}
	void insert_vertex(T n) {
		root = insert(root, n);
	}
	void insert_edge(T a, T b, int weight) {
		Vertex<T> *va, *vb;
		for(Vertex<T>* p = root; p; p = p->vertex) {
			if(p->data == a) va = p;
			if(p->data == b) vb = p;
		}
		va->edge = insert(va->edge, vb, weight);
	}
	void read_file(std::string file) {
		T n1, n2;
		std::ifstream f(file);
		int vc;
		f >> vc;
		for(int i=0; i<vc; i++) {
			f >> n1;
			insert_vertex(n1);
		}
		int wt;
		while(f >> n1 >> n2 >> wt) insert_edge(n1, n2, wt);
	}

	void view() {
		for(Vertex<T>* p = root; p; p = p->vertex) {
			std::cout << p->data << " : ";
			for(Edge<T>* e = p->edge; e; e = e->edge) 
				std::cout << '<' << p->data << ',' << e->vertex->data << '>' << e->weight << ' '; 
			std::cout << std::endl;
		}
	}
	Vertex<T>* data() {
		return root;
	}
	void prim() {
		clearv();
		root->v = 1;//below for syntax is just to call n-1 times
		for(Vertex<T>* q = root->vertex; q; q = q->vertex) shortest(root);
	}
	void topology() {//check v to entry and print data
		clearv();
		for(Vertex<T>* q; q = find_entry(root);) {
			q->v = 1;
			std::cout << q->data << " - ";
		}
	}

	int floyd(T a, T b) {
		clearv();
		std::map<T, std::map<T, int>> A;
		for(Vertex<T>* q = root; q; q = q->vertex) 
			for(Vertex<T>* p = root; p; p = p->vertex) 
				A[q->data][p->data] = INT_MAX / 2;
		for(Vertex<T>* q = root; q; q = q->vertex) 
			for(Edge<T>* e = q->edge; e; e = e->edge) 
				A[q->data][e->vertex->data] = e->weight;
		
		for(Vertex<T>* k = root; k; k = k->vertex) 
			for(Vertex<T>* i = root; i; i = i->vertex) 
				for(Vertex<T>* j = root; j; j = j->vertex) 
					A[i->data][j->data] = min(A[i->data][j->data], 
							A[i->data][k->data] + A[k->data][j->data]);
		return A[a][b];
	}
	int dijkstra(T a, T b) {
		clearv();
		distance.clear();
		for(Vertex<T>* p = root; p; p = p->vertex) distance[p] = INT_MAX / 2;
		Vertex<T>* pa = find(root, a); assert(pa);
		Vertex<T>* pb = find(root, b); assert(pb);
		distance[pa] = 0;
		while(pb != find_closest());
		for(auto& a : waypoint[pb]) a->v = 1;
		return distance[pb];
	}
	void depth() {
		clearv();
		depth(root);
	}
	void breadth() {
		clearv();
		std::cout << root->data << ' ';
		root->v = 1;
		breadth(root);
	}
	void bridge() {
		clearv();
		std::vector<Edge<T>*> v;
		for(Vertex<T>* p = root; p; p = p->vertex) 
			for(Edge<T>* e = p->edge; e; e = e->edge)
				if(is_bridge(p, e)) v.push_back(e);
		for(auto& a : v) a->v = 1;
	}
	void greedy() {
		clearv();
		union_set.clear();
		int i = 1;
		for(Vertex<T>* p = root; p; p = p->vertex) union_set[p] = i++;
		std::vector<Edge<T>*> v;
		for(Vertex<T>* p = root->vertex; p; p = p->vertex) v.push_back(find_greed());
		clearv();
		for(auto& a : v) a->v = 1;
	}

protected:
	Vertex<T>* root = nullptr;
	Vertex<T>* insert(Vertex<T>* p, T n) {//recursively insert a value 'n'
		if(!p) {
			p = new Vertex<T>;
			p->data = n;
			return p;
		}
		p->vertex = insert(p->vertex, n);
		return p;
	}
	Edge<T>* insert(Edge<T>* e, Vertex<T>* v, int weight) {
		if(!e) {//recursively insert edge in at the end of e pointint to v
			e = new Edge<T>;
			e->vertex = v;
			e->weight = weight;
			return e;
		}
		e->edge = insert(e->edge, v, weight);
		return e;
	}
	bool is_bridge(Vertex<T>* p, Edge<T>* eg) {//check all the bridges in the graph
		eg->v = 1;
		for(Edge<T>* e = eg->vertex->edge; e; e = e->edge) 
			if(e->vertex == p) e->v = 1;
		depth(eg->vertex);
		bool r = !p->v;
		clearv();
		return r;
	}

private:
	std::map<Vertex<T>*, int> distance;
	std::map<Vertex<T>*, std::vector<Edge<T>*>> waypoint;
	std::map<Vertex<T>*, int> union_set;
	Vertex<T>* find_closest() {//dijkstra
		int min = INT_MAX / 2;
		Vertex<T>* p = nullptr;
		for(auto& a : distance) if(min > a.second && !a.first->v) {
			p = a.first;
			min = a.second;
		}
		p->v = 1;
		for(Edge<T>* e = p->edge; e; e = e->edge) if(!e->vertex->v) {
			if(distance[e->vertex] > distance[p] + e->weight) {
				distance[e->vertex] = distance[p] + e->weight;
				waypoint[e->vertex] = waypoint[p];
				waypoint[e->vertex].push_back(e);
			}
		}
		//for(auto& a : distance) std::cout << a.first->data << ' ' << a.second << 
		//	' ' << a.first->v << std::endl;
		return p;
	}
	Vertex<T>* find(Vertex<T>* p, T n) {//find value 'n' and return the address
		for(Vertex<T>* v = p; v; v = v->vertex) if(v->data == n) return v;
	}
	void depth(Vertex<T>* p) {//depth search the graph
		assert(p);
		p->v = 1;
		std::cout << p->data << ' ';
		for(Edge<T>* e = p->edge; e; e = e->edge) {
			if(!e->vertex->v && !e->v) {//!e->v is for bridge func
				e->v = 1;
				depth(e->vertex);
			}
		}
	}
	void breadth(Vertex<T>* p) {
		std::vector<Vertex<T>*> q;
		for(Edge<T>* e = p->edge; e; e = e->edge) {
			if(!e->vertex->v) {
				q.push_back(e->vertex);
				e->v = 1;
				std::cout << e->vertex->data << ' ';
				e->vertex->v = 1;
			}
		}
		for(auto& a : q) breadth(a);
	}
	void efree(Edge<T>* e) {
		if(!e) return;
		efree(e->edge);
		delete e;
	}
	void gfree(Vertex<T>* p) {
		if(!p) return;
		efree(p->edge);
		gfree(p->vertex);
		delete p;
	}
	void clearv() {
		for(Vertex<T>* p = root; p; p = p->vertex) {
			p->v = 0;
			for(Edge<T>* e = p->edge; e; e = e->edge) e->v = 0;
		}
	}
	void shortest(Vertex<T>* p) {//prim
		Edge<T>* me;
		int min = INT_MAX;
		for(; p; p = p->vertex) {
			if(p->v) {
				for(Edge<T>* e = p->edge; e; e = e->edge) {
					if(e->v) continue;
					if(e->weight < min && !e->vertex->v) {
						min = e->weight;
						me = e;
					}
				}
			}
		}
		me->v = 1;
		me->vertex->v = 1;
	}
	Vertex<T>* find_entry(Vertex<T>* p) {//return NULL when no more,topology
		for(Vertex<T>* q = p; q; q = q->vertex) {
			if(q->v != 1) {//1 or 2 or 0
				for(Edge<T>* e = q->edge; e; e = e->edge) {
					if(!e->vertex->v) e->vertex->v = 2;//entry marking
				}
			}
		}
		Vertex<T>* r = NULL;
		for(Vertex<T>* q = p; q; q = q->vertex) {
			if(q->v == 2) q->v = 0;
			else if(!q->v) r = q;
		}
		return r;
	}
	void unite(Vertex<T>* a, Vertex<T>* b) {//greed
		for(auto& u : union_set) 
			if(u.second == union_set[a]) u.second = union_set[b];
	}
	Edge<T>* find_greed() {
		int min = INT_MAX / 2;
		Edge<T>* eg;
		Vertex<T>* vt;
		for(Vertex<T>* p = root; p; p = p->vertex) {
			for(Edge<T>* e = p->edge; e; e = e->edge) {
				if(!e->v && e->weight < min) {
					min = e->weight;
					eg = e;
					vt = p;
				}
			}
		}
		eg->v = 1;
		if(union_set[vt] != union_set[eg->vertex]) {
			unite(vt, eg->vertex);
			return eg;
		} else return find_greed();
	}
};


template <typename T> class Tree : public Graph<T>
{
public:
	void insert(T n) {
		Graph<T>::insert_vertex(n);
		Vertex<T>* p;
		for(p = Graph<T>::root; p->vertex; p = p->vertex);
		if(Graph<T>::root->vertex) Graph<T>::root = insert(Graph<T>::root, p);
	}
	Vertex<T>* find(T n) {
		return find(Graph<T>::root, n);
	}
		
private:
	Vertex<T>* find(Vertex<T>* p, T n) {
		if(p->data == n) return p;//all below is <else if> due to return
		if(!p->edge) return nullptr;
		if(p->data < n == p->data < p->edge->vertex->data) 
			return find(p->edge->vertex, n);
		if(!p->edge->edge) return nullptr;
		return find(p->edge->edge->vertex, n);
	}
	Vertex<T>* insert(Vertex<T>* p, Vertex<T>* n) {//insert by comparing value
		if(!p) return n;						//to make binary tree
		if(!p->edge) p->edge = Graph<T>::insert(p->edge, n, 0);//no son
		else if(!p->edge->edge) {//1 son
			if(p->data < p->edge->vertex->data == p->data < n->data)
				insert(p->edge->vertex, n);
			else p->edge = Graph<T>::insert(p->edge, n, 0);
		} else {//2son
			if(p->data < p->edge->vertex->data == p->data < n->data)
				insert(p->edge->vertex, n);
			else insert(p->edge->edge->vertex, n);
		}
		return p;
	}
};

template <typename T> class ParseTree : public Tree<T>
{
public:
	ParseTree(std::string expression) {
		int type = 0;
		if(is_operator(expression.front())) type = -1;
		else if(is_operator(expression.back())) type = 1;
		for(auto& a : expression) expr.push_back(a);
		switch(type) {
			case -1:
				Graph<T>::root = finsert();
				break;
			case 0:
				Graph<T>::root = insert(expression);
				break;
			case 1:
				Graph<T>::root = binsert();
		}
		connect(Graph<T>::root);
		Vertex<T>* p = Graph<T>::root;
		for(int i=1; i<vts.size(); i++) {
			p->vertex = vts[i];
			p = p->vertex;
		}
	}

	void forward() {
		forward(Graph<T>::root);
	}
	void middle() {
		middle(Graph<T>::root);
	}
	void back() {
		back(Graph<T>::root);
	}

private:
	std::deque<char> expr;
	std::vector<Vertex<T>*> vts;
	void forward(Vertex<T>* p) {
		std::cout << p->data;
		if(p->edge) {
			forward(p->edge->vertex);
			forward(p->edge->edge->vertex);
		}
	}
	void middle(Vertex<T>* p) {
		if(p->edge) middle(p->edge->vertex);
		std::cout << p->data;
		if(p->edge) middle(p->edge->edge->vertex);
	}
	void back(Vertex<T>* p) {
		if(p->edge) {
			back(p->edge->vertex);
			back(p->edge->edge->vertex);
		}
		std::cout << p->data;
	}
	void connect(Vertex<T>* p) {//connect vertexes for graph compatibility
		vts.push_back(p);
		if(p->edge) {
			connect(p->edge->vertex);
			connect(p->edge->edge->vertex);
		}
	}
	Vertex<T>* insert(std::string s) {
		int token = div_point(s);
		Vertex<T>* p = new Vertex<T>;
		p->data = s[token];
		if(token) {
			std::string rhs = s.substr(token + 1);
			s.erase(token);
			p->edge = Graph<T>::insert(p->edge, insert(s), 0);//crash
			p->edge = Graph<T>::insert(p->edge, insert(rhs), 0);
		}
		return p;
	}
	
	int div_point(std::string s) {
		std::stack<char> parenthesis;
		int token = 0;
		for(int i=0; i<s.size(); i++) {
			if(s[i] == '(') parenthesis.push('(');
			else if(s[i] == ')') parenthesis.pop();
			else if(parenthesis.empty()) {
				if(s[i] == '+' || s[i] == '-') {
					token = i;
					break;
				} else if(s[i] == '*' || s[i] == '/') if(!token) token = i;
			}
		}
		return token;
	}
	bool is_operator(char c) {
		for(auto& a : {'+', '-', '*', '/'}) if(c == a) return true;
		return false;
	}
	Vertex<T>* finsert() {
		Vertex<T>* p = new Vertex<T>;
		p->data = expr.front();
		expr.pop_front();
		if(is_operator(p->data)) {
			p->edge = Graph<T>::insert(p->edge, finsert(), 0);
			p->edge = Graph<T>::insert(p->edge, finsert(), 0);
		}
		return p;
	}
	Vertex<T>* binsert() {
		std::stack<Vertex<T>*> st;
		while(!expr.empty()) {
			do {
				Vertex<T>* vt = new Vertex<T>;
				vt->data = expr.front(); expr.pop_front();
				st.push(vt); 
			} while(!is_operator(st.top()->data)); 
			Vertex<T>* p1 = st.top(); st.pop();
			Vertex<T>* p3 = st.top(); st.pop();
			Vertex<T>* p2 = st.top(); st.pop();
			p1->edge = Graph<T>::insert(p1->edge, p2, 0);
			p1->edge = Graph<T>::insert(p1->edge, p3, 0);
			st.push(p1);
		}
		return st.top();
	}


};



