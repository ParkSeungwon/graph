#include"special.h"
using namespace std;

GraphView<V, E, shared_ptr<MindNode>>::GraphView(V* gr) 
{
	root = gr;
	Point im{500, 500};
	int i = 0, sz = 0;
	allocate_node(gr);//populate vpNpos, arrows_
	generate_graph();//populate drawables_
}

GraphView<V, E, shared_ptr<MindNode>>::~GraphView() 
{
	std::string dir = root->edge->vertex->data->path;
	save_graph(root, dir);
}

void GraphView<V, E, shared_ptr<MindNode>>::allocate_node(V* vt) 
{//allocate all the sub nodes of vt
	if(!vt) return;
	if(vpNpos.find(vt) == vpNpos.end()) vpNpos[vt] = {500,500};
	for(E* e = vt->edge; e; e = e->edge) {//x, y is relative coord to parent
		if(e->vertex) {
			vpNpos[e->vertex] = vpNpos[vt] + e->vertex->data->pt;//edge와 v가 바뀜
			arrows_.push_back(std::make_tuple(vt, e->vertex, e->weight, e->v));
			allocate_node(e->vertex);
		}
	}
}

V* GraphView<V, E, shared_ptr<MindNode>>::get_parent(V* s) 
{///get parent node of son
	if(s == root) return nullptr;
	for(auto* v = root; v; v = v->vertex) 
		for(auto* e = v->edge; e; e = e->edge) if(e->vertex == s) return v;
}

void GraphView<V, E, shared_ptr<MindNode>>::drag(Point from, Point to) 
{///virtual can find specialization method
	V *pf = pick(from), *pt = pick(to), *parent = get_parent(pf);
	if(pf && pt && pt->data->type == MindNode::Dir) {
		bool same_name = false, paste_to_sub = false;
		width_apply(pf, [&](std::shared_ptr<MindNode> sp) {
				if(sp == pt->data) paste_to_sub = true; });
		for(auto* e = pt->edge; e; e = e->edge) 
			if(e->vertex->data->name == pf->data->name) same_name = true;
		if(!paste_to_sub && !same_name) {
			std::string command = "mv ";
			command += pf->data->path + pf->data->name + ' ';
			command += pt->data->path + pt->data->name;
			system(command.data());//move file or directory
			cutNpaste(pf, pt);//move edge, !!!buggy
		}
		to += Point{100, 0};
	}
	
	vpNpos[pf] = to;
	//apply lambda function to all sub of a.first vertex 
	width_apply(pf, [&](std::shared_ptr<MindNode> sp) {
		for(auto& b : vpNpos) //if sub & not clogged together
			if(b.first->data == sp && abs(b.second - from) > 20)
				b.second += to - from;//parallel move
	});
	pf->data->pt = parent ? to - vpNpos[parent] : 0;
	//std::cout << a.second << ' ' << a.first->data->pt << std::endl;
	generate_graph();
}

void GraphView<V, E, shared_ptr<MindNode>>::right_click(Point pt) 
{///popup to configure node
	for(auto& a : vpNpos) {
		if(abs(a.second - pt) < 20) {
			popup(a.first);
			break;
		}
	}
	generate_graph();
}

std::vector<std::shared_ptr<Drawable>>::const_iterator 
GraphView<V, E, shared_ptr<MindNode>>::begin() const 
{
	return drawables_.begin();
}

std::vector<std::shared_ptr<Drawable>>::const_iterator 
GraphView<V, E, shared_ptr<MindNode>>::end() const 
{
	return drawables_.end();
}

void GraphView<V, E, shared_ptr<MindNode>>::treeview(int height) 
{
	width_ = pow(2, height) * CIRCLE_SIZE;
	treeview(root, width_ / 2, 100, 1);
	generate_graph();
}

void GraphView<V, E, shared_ptr<MindNode>>::cutNpaste(V* from, V* to) 
{///cut an edge from 'from' paste to 'to'
	std::string from_path = from->data->path, to_path = to->data->path;
	from->data->path = to_path;
	width_apply(from, [&](std::shared_ptr<MindNode> sp) {
			sp->path.replace(sp->path.find(from_path), from_path.size(), to_path);});
	V* parent = get_parent(from);
	E* tmp;
	for(E* e = parent->edge; e; e = e->edge) {//cut edge
		if(e->edge && e->edge->vertex == to) {
			tmp = e->edge;
			e->edge = e->edge->edge;
			tmp->edge = nullptr;
			break;
		}
	}
	for(E* e = to->edge; e; e = e->edge) {//paste edge
		if(!e->edge) {
			e->edge = tmp;
			break;
		}
	}
	for(auto& a : arrows_) 
		if(get<0>(a) == parent && get<1>(a) == from) get<0>(a) = to;
//	vpNpos.clear();
//	arrows_.clear();
//	allocate_node(root);
}

void GraphView<V, E, shared_ptr<MindNode>>::treeview(V* p, int x, int y, int h) 
{
	if(!p) return;
	vpNpos[p] = {x, y};
	if(p->edge) {
		treeview(p->edge->vertex, x - width_ / pow(2, h + 1), y+100, h + 1);
		if(p->edge->edge) treeview(p->edge->edge->vertex, 
				x + width_ / pow(2, h + 1), y + 100, h + 1);
	}
}

void GraphView<V, E, shared_ptr<MindNode>>::generate_graph() 
{
	drawables_.clear();
	for(auto& a : arrows_) {//reconfigure arrows tip positions according to vertex
		V* v = std::get<1>(a);//position
		auto d1 = vpNpos[std::get<0>(a)];//starting point
		auto d2 = vpNpos[v];//ending point
		auto d3 = CIRCLE_SIZE * (d2 - d1) / abs(d2 - d1);
		d1 += d3;//make arrow stop before circle
		d2 -= d3;
		Arrow arrow{d1, d2, 1};
		arrow.txt(std::get<2>(a));//show weight
		//if(std::get<3>(a)) arrow.set_rgb(0,0,1);//if v is marked
		arrow.set_rgb((double)v->data->r / 255, (double)v->data->g / 255,
				(double)v->data->b / 255);
		drawables_.push_back(std::make_shared<Arrow>(arrow));
	}
	for(auto& a : vpNpos) {//draw nodes according to shape of data
		int sz = CIRCLE_SIZE / 2;
		int w = a.first->data->name.size() * CIRCLE_SIZE / 10;
		w = std::max(w, sz);
		if(a.first->data->outline == MindNode::Ellipse) {
			Ellipse el{a.second - Point{w, sz}, a.second + Point{w, sz}};
			el.txt(a.first->data->name);
			el.set_rgb((double)a.first->data->r / 255, 
				(double)a.first->data->g / 255, (double)a.first->data->b / 255);
			drawables_.push_back(std::make_shared<Ellipse>(el));
		} else if(a.first->data->outline == MindNode::Rect) {
			Box bx{a.second - Point{w*2, sz*2}, a.second + Point{w*2, sz*2}};
			bx.txt(a.first->data->name);
			drawables_.push_back(std::make_shared<Box>(bx));
		} else if(a.first->data->outline == MindNode::Diamond) {
			Pix im{a.first->data->path + a.first->data->name, 
				a.second - Point{w*3, sz*3}, a.second + Point{w*3, sz*3}};
			im.txt(a.first->data->name);
			drawables_.push_back(std::make_shared<Pix>(im));
		}
	}
}

V* GraphView<V, E, shared_ptr<MindNode>>::pick(Point p) 
{//returns a V* at that position, if none return null
	for(auto& a : vpNpos) if(abs(a.second - p)<20) return a.first;
	return nullptr;
}
