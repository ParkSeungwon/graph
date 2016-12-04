#pragma once
#include<climits>
#include<iostream>
#include<map>
#define min(a, b) a < b ? a : b

template <typename T> class Vertex;
template<typename T> class Edge
{
public:
	int weight;
	int v;
	struct Vertex<T>* vertex;
	struct Edge<T>* edge;
};

template<typename T> class Vertex
{
public:
	T data;
	int v;
	struct Edge<T>* edge;
	struct Vertex<T>* vertex;
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
		root->v = 1;//below for syntax is just to call n-1 times
		for(Vertex<T>* q = root->vertex; q; q = q->vertex) shortest(root);
	}
	void clearv() {
		for(Vertex<T>* p = root; p; p = p->vertex) {
			p->v = 0;
			for(Edge<T>* e = p->edge; e; e = e->edge) e->v = 0;
		}
	}

	void topology() {//check v to entry and print data
		for(Vertex<T>* q; q = find_entry(root);) {
			q->v = 1;
			std::cout << q->data << " - ";
		}
	}

	int floyd(T a, T b) {
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

protected:
	Vertex<T>* root = nullptr;
	Vertex<T>* insert(Vertex<T>* p, T n) {
		if(!p) {
			p = (Vertex<T>*)malloc(sizeof(Vertex<T>));
			p->data = n;
			p->v = 0;
			p->edge = nullptr;
			p->vertex = nullptr;
			return p;
		}
		p->vertex = insert(p->vertex, n);
		return p;
	}
	Edge<T>* insert(Edge<T>* e, Vertex<T>* v, int weight) {
		if(!e) {
			e = (Edge<T>*)malloc(sizeof(Edge<T>));
			e->edge = nullptr;
			e->vertex = v;
			e->weight = weight;
			e->v = 0;
			return e;
		}
		e->edge = insert(e->edge, v, weight);
		return e;
	}

private:
	void efree(Edge<T>* e) {
		if(!e) return;
		efree(e->edge);
		free(e);
	}
	void gfree(Vertex<T>* p) {
		if(!p) return;
		efree(p->edge);
		gfree(p->vertex);
		free(p);
	}
	void shortest(Vertex<T>* p) {
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
	Vertex<T>* find_entry(Vertex<T>* p) {//return NULL when no more
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
	Vertex<T>* insert(Vertex<T>* p, Vertex<T>* n) {
		if(!p) return n;
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


