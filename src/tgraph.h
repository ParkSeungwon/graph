#pragma once
#include<iostream>

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
				if(e->vertex) std::cout << '<' << p->data << ',' << e->vertex->data << '>' << e->weight << ' '; 
			std::cout << std::endl;
		}
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
};


template <typename T> class Tree : public Graph<T>
{
public:
	void insert(T n) {
		Graph<T>::insert_vertex(n);
		Vertex<T>* p;
		for(p = Graph<T>::root; p->vertex; p = p->vertex);
		p->edge = Graph<T>::insert(p->edge, nullptr, 0);
		p->edge = Graph<T>::insert(p->edge, nullptr, 0);
		if(Graph<T>::root->vertex) Graph<T>::root = insert(Graph<T>::root, p);
	}
		
private:
	Vertex<T>* insert(Vertex<T>* p, Vertex<T>* n) {
		if(!p) return n;
		if(n->data < p->data) p->edge->vertex = insert(p->edge->vertex, n);
		else p->edge->edge->vertex = insert(p->edge->edge->vertex, n);
		return p;
	}
};


