#include<memory>
#include"graphv.h"
#include"mindmap.h"

template<typename V, typename E> class GraphView<V, E, std::shared_ptr<MindNode>> 
{//template specialization for MindNode
public:
	GraphView(V* gr) {
		root = gr;
		Point im{500, 500};
		int i = 0, sz = 0;
		allocate_node(gr);
		generate_graph();
	}

	void allocate_node(V* vt) {//allocate all the sub nodes of vt
		if(!vt) return;
		if(map_.find(vt) == map_.end()) map_[vt] = {500,500};
		for(E* e = vt->edge; e; e = e->edge) {//x, y is relative coord to parent
			if(e->vertex) {
				map_[e->vertex] = map_[vt] + e->vertex->data->pt;
				arrows_.push_back(std::make_tuple(vt, e->vertex, e->weight, e->v));
				allocate_node(e->vertex);
			}
		}
	}

	void drag(Point from, Point to) {
		drawables_.clear();
		for(auto& a : map_) {
			if(abs(a.second - from) < 20) {
				auto parent = a.second - a.first->data->pt; 
				a.second = to;
				a.first->data->pt = to - parent;
				break;//select only one
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
			auto d1 = map_[std::get<0>(a)];//starting point
			auto d2 = map_[std::get<1>(a)];//ending point
			auto d3 = CIRCLE_SIZE * (d2 - d1) / abs(d2 - d1);
			d1 += d3;//make arrow stop before circle
			d2 -= d3;
			Arrow arrow{d1, d2, 1};
			arrow.txt(std::get<2>(a));//show weight
			if(std::get<3>(a)) arrow.set_rgb(0,0,1);//if v is marked
			drawables_.push_back(std::make_shared<Arrow>(arrow));
		}
		for(auto& a : map_) {
			int sz = CIRCLE_SIZE / 2;
			Ellipse el{a.second - Point{sz, sz}, a.second + Point{sz, sz}};
			el.txt(a.first->data->name);
			drawables_.push_back(std::make_shared<Ellipse>(el));
		}
	}
};

