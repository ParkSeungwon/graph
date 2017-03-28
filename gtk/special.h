#include<memory>
#include"graphv.h"
#include"mindmap.h"
#include"image.h"

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
	virtual ~GraphView() {
		std::string dir = root->edge->vertex->data->path;
		save_graph(root, dir);
	}

	void allocate_node(V* vt) {//allocate all the sub nodes of vt
		if(!vt) return;
		if(map_.find(vt) == map_.end()) map_[vt] = {500,500};
		for(E* e = vt->edge; e; e = e->edge) {//x, y is relative coord to parent
			if(e->vertex) {
				map_[e->vertex] = map_[vt] + e->vertex->data->pt;//edge와 v가 바뀜
				arrows_.push_back(std::make_tuple(vt, e->vertex, e->weight, e->v));
				allocate_node(e->vertex);
			}
		}
	}
	V* get_parent(V* s) {
		if(s == root) return nullptr;
		for(auto* v = root; v; v = v->vertex) 
			for(auto* e = v->edge; e; e = e->edge) if(e->vertex == s) return v;
	}

	virtual void drag(Point from, Point to) {//virtual can find specialization method
		drawables_.clear();
		for(auto& a : map_) {
			if(abs(a.second - from) < 20) {
				auto* parent = get_parent(a.first);
				a.second = to;
				//apply lambda functio to all sub of a.first vertex 
				width_apply(a.first, [&](std::shared_ptr<MindNode> sp) {
					for(auto& b : map_) if(b.first->data == sp && //if sub
						abs(b.second - from) > 20)//if not clogged together
								b.second += to - from;});//parallel move
				a.first->data->pt = parent ? to - map_[parent] : 0;
				std::cout << a.second << ' ' << a.first->data->pt << std::endl;
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

	template<typename T> void width_apply(V* p, T func) {
		for(auto* e = p->edge; e; e = e->edge) {
			func(e->vertex->data);
			if(e->vertex->data->type == MindNode::Dir) width_apply(e->vertex, func);
		}
	}
	
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
			V* v = std::get<1>(a);
			auto d1 = map_[std::get<0>(a)];//starting point
			auto d2 = map_[v];//ending point
			auto d3 = CIRCLE_SIZE * (d2 - d1) / abs(d2 - d1);
			d1 += d3;//make arrow stop before circle
			d2 -= d3;
			Arrow arrow{d1, d2, 1};
			arrow.txt(std::get<2>(a));//show weight
			//if(std::get<3>(a)) arrow.set_rgb(0,0,1);//if v is marked
			arrow.set_rgb((double)v->data->r / 255, (double)v->data->b / 255, 
					(double)v->data->g / 255);
			drawables_.push_back(std::make_shared<Arrow>(arrow));
		}
		for(auto& a : map_) {
			int sz = CIRCLE_SIZE / 2;
			int w = a.first->data->name.size() * CIRCLE_SIZE / 10;
			w = std::max(w, sz);
			if(a.first->data->outline == MindNode::Ellipse) {
				Ellipse el{a.second - Point{w, sz}, a.second + Point{w, sz}};
				el.txt(a.first->data->name);
				drawables_.push_back(std::make_shared<Ellipse>(el));
			} else if(a.first->data->outline == MindNode::Rect) {
				Box bx{a.second - Point{w*2, sz*2}, a.second + Point{w*2, sz*2}};
				bx.txt(a.first->data->name);
				drawables_.push_back(std::make_shared<Box>(bx));
			} else if(a.first->data->outline == MindNode::Diamond) {
				Pix im{a.first->data->path + a.first->data->name, 
					a.second - Point{2*w, sz*2}, a.second + Point{w*2, sz * 2}};
				//im.txt(a.first->data->name);
				drawables_.push_back(std::make_shared<Pix>(im));
			}
		}
	}
};
