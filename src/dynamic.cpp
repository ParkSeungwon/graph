#include"tgraph.h"
using namespace std;

int main()
{
	Graph<int> g;
	for(int i=0; i<25; i++) g.insert_vertex(i);
	int wr[5][4] = {{3,2,4,0},{3,2,4,1},{0,7,3,4},{3,3,0,2},{1,3,0,2}};
	int wc[4][5] = {{1,0,2,4,3},{4,6,5,2,1},{4,4,5,2,1},{5,6,8,5,3}};

//	for(int j=0; j<5; j++) for(int i=0; i<4; i++) wr[j][i] = - wr[j][i];
//	for(int j=0; j<4; j++) for(int i=0; i<5; i++) wc[j][i] = - wc[j][i];
	for(int j=0; j<5; j++) for(int i=0; i<4; i++) 
		g.insert_edge(j*5+i, j*5+i+1, wr[j][i]);
	for(int j=0; j<4; j++) for(int i=0; i<5; i++) {
		g.insert_edge(j*5+i, j*5+i+5, wc[j][i]);
		cout << j*5+i << "->" << j*5+i+5 << " = " << wc[j][i] << endl;
	}
	g.dijkstra(0,24);
	//g.prim();
	g.view();
	int sum = 0;
	for(auto* v = g.data(); v; v = v->vertex) for(auto* e = v->edge; e; e = e->edge) 
		if(e->v) {
			cout << v->data << "->" << e->vertex->data << endl;
			sum += e->weight;
		}
	cout << sum << endl;

}

