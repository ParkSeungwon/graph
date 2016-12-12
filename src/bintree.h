#pragma once
#include"tgraph.h"
#define max(a,b) a > b ? a : b
template <typename T> class Tree : public Graph<T>
{
public:
	void insert(T n) {
		Graph<T>::insert_vertex(n);
		Vertex<T>* p;
		for(p = Graph<T>::root; p->vertex; p = p->vertex);//set p to n
		p->edge = Graph<T>::insert(p->edge, nullptr, 0);
		p->edge = Graph<T>::insert(p->edge, nullptr, 0);
		if(Graph<T>::root->vertex) Graph<T>::root = insert(Graph<T>::root, p);
	}
	Vertex<T>* find(T n) {
		return find(Graph<T>::root, n);
	}
	int height() {
		return height(Graph<T>::root);
	}
		
private:
	int height(Vertex<T>* tree) {
		if(!tree) return 0;
		return 1 + max(height(tree->edge->vertex), height(tree->edge->edge->vertex));
	}
	Vertex<T>* find(Vertex<T>* p, T n) {
		if(!p) return nullptr;
		if(p->data == n) return p;//all below is <else if> due to return
		if(n< p->data) return find(p->edge->vertex, n);
		else return find(p->edge->edge->vertex, n);
	}
	Vertex<T>* insert(Vertex<T>* p, Vertex<T>* n) {//insert by comparing value
		if(!p) return n;						//to make binary tree
		int lh = height(p->edge->vertex);
		int rh = height(p->edge->edge->vertex);
		if(n->data < p->data) {
			p->edge->vertex = insert(p->edge->vertex, n);
			if(lh > rh) return rotate_LL(p);
		} else {
			p->edge->edge->vertex = insert(p->edge->edge->vertex, n);
			if(lh < rh) return rotate_RR(p);
		}
	}

	Vertex<T>* rotate_LL(Vertex<T>* A) {
		Vertex<T>* B = A->edge->vertex;
		A->edge->vertex = B->edge->edge->vertex;
		B->edge->edge->vertex = A;
		return B;
	}
	Vertex<T>* rotate_RR(Vertex<T>* A) {
		Vertex<T>* B = A->edge->vertex;
		A->edge->edge->vertex = B->edge->vertex;
		B->edge->vertex = A;
		return B;
	}	
};
