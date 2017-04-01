#include"tgraph.h"
using namespace std;
typedef Vertex<int> V;
typedef Edge<int> E;

V* get_parent(V* s, V* root) 
{///get parent node of son
	if(s == root) return nullptr;
	for(auto* v = root; v; v = v->vertex) 
		for(auto* e = v->edge; e; e = e->edge) if(e->vertex == s) return v;
}

void move(V* from, V* to, V* root) {
	V* parent = get_parent(from, root);
	E *tmp;
	for(E* e = parent->edge, *prev = parent->edge; e; prev = e, e = e->edge) {//cut edge
		if(e->vertex == from) {
			tmp = e;
			if(e != parent->edge) prev->edge = e->edge;
			else parent->edge = e->edge;
			tmp->edge = nullptr;
			break;
		}
		//prev = e;
	}
	for(E* e = to->edge; e; e = e->edge) {//paste edge
		if(!e->edge) {
			e->edge = tmp;
			break;
		}
	}
}

int main()
{
	Graph<int> g;
	for(int i=0; i<3; i++) g.insert_vertex(i);
	for(int i=0; i<2; i++) g.insert_edge(i, i+1, 0);
	g.view();
	V* r = g.data();
	move(r->vertex->vertex, r, r);
	g.view();
}

