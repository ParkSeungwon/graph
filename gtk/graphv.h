//A class to view a graph data structure
#pragma once
#include<complex>
#include"drawable.h"
#include"src/parsetree.h"
#define CIRCLE_SIZE 30.0
//V Vertex should have vertex, edge, data, v
//E Edge should have vertex, edge, weight, v
//D Data can be anything
template <typename V, typename E, typename D> class GraphView 
{
public:
	GraphView(V* gr) {
		root = gr;
		Point im{500, 500};
		int i = 0, sz = 0;
		for(V* p = gr; p; p = p->vertex) sz++;
		for(V* p = gr; p; p = p->vertex) {
			map_[p] = im + std::polar(200.0, M_PI * 2.0 * i++ / sz);
			std::cout << "coordination is " << map_[p] << std::endl;
			for(E* q = p->edge; q; q = q->edge) if(q->vertex) //if is for treeview
				arrows_.push_back(std::make_tuple(p, q->vertex, q->weight, q->v));
		}
		generate_graph();
	}

	virtual ~GraphView(){}//need this for specialization destructor
	virtual void drag(Point f, Point t) {
		drawables_.clear();
		for(auto& a : map_) {
			if(abs(a.second - f) < 20) {
				a.second = t;
				break;
			}
		}
		generate_graph();
	}

	std::vector<std::shared_ptr<Drawable>>::const_iterator begin() const {
		return drawables_.begin();
	}
	
	std::vector<std::shared_ptr<Drawable>>::const_iterator end() const {
		return drawables_.end();
	}
	
	void treeview(int height) {
		drawables_.clear();
		width_ = pow(2, height) * CIRCLE_SIZE;
		treeview(root, width_ / 2, 100, 1);
		generate_graph();
	}
	

protected:
	V* root = nullptr;
	std::map<V*, Point> map_;
	std::vector<std::tuple<V*, V*, int, int>> arrows_;
	std::vector<std::shared_ptr<Drawable>> drawables_;

private:
	int width_;
	
	void treeview(V* p, int x, int y, int h) {
		if(!p) return;
		map_[p] = {x, y};
		if(p->edge) {
			treeview(p->edge->vertex, x - width_ / pow(2, h + 1), y+100, h + 1);
			if(p->edge->edge) treeview(p->edge->edge->vertex, 
					x + width_ / pow(2, h + 1), y + 100, h + 1);
		}
	}
	
	void generate_graph() {
		for(auto& a : arrows_) {
			auto d1 = map_[std::get<0>(a)];
			auto d2 = map_[std::get<1>(a)];
			auto d3 = CIRCLE_SIZE * (d2 - d1) / abs(d2 - d1);
			d1 += d3;
			d2 -= d3;
			Arrow arrow{d1, d2, 1};
			arrow.txt(std::get<2>(a));
			if(std::get<3>(a)) arrow.set_rgb(0,0,1);
			drawables_.push_back(std::make_shared<Arrow>(arrow));
		}
		for(auto& a : map_) {
			int sz = CIRCLE_SIZE / 2;
			Ellipse el{a.second - Point{sz, sz}, a.second + Point{sz, sz}};
			el.txt(a.first->data);
			drawables_.push_back(std::make_shared<Ellipse>(el));
		}
	}
};

template <typename T> class GraphV : public GraphView<Vertex<T>, Edge<T>, T>
{
public:
	GraphV(Vertex<T>* data) : GraphView<Vertex<T>, Edge<T>, T>(data) {}
};

