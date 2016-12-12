#pragma once
#include"tgraph.h"
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
