#include"graphview.h"
using namespace std;

GraphView::GraphView()
{//can allocate only a part of a graph
	ifstream f("~/.mindmap");
	f >> *this;
}

GraphView::~GraphView() 
{
	ofstream f("~/.mindmap");
	f << *this;
}

void GraphView::generate_drawables(V* from)
{
	allocate_node(from);//recursively populate vpNpos, arrows_
	generate_graph();//populate drawables_
}

void GraphView::allocate_node(const V* vt) 
{//allocate all the sub nodes of vt
	if(!vt) return;
	if(vpNpos.find(vt) == vpNpos.end()) vpNpos[vt] = {1000,1000};//if root
	for(E* e = vt->edge; e; e = e->edge) {//x, y is relative coord to parent
		if(e->vertex) {
			vpNpos[e->vertex] = vpNpos[vt] + Point{e->weight / 10000, e->weight % 10000};//edge와 v가 바뀜
			arrows_.push_back(std::make_tuple(vt, e->vertex, e->weight, e->v));
			allocate_node(e->vertex);
		}
	}
}

void GraphView::drag(Point from, Point to) 
{///virtual can find specialization method
	V *pf = pick(from), *pt = pick(to);
	if(!pf || pf == pt) return;
	V* parent = get_parent(pf);
	if(pt && pt->data->type == MindNode::Dir) {
		bool same_name = false, paste_to_sub = false;
		sub_apply(pf->data, [&](const MindNode& sp) {
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
		pf->data->pt = Point{100,0};//this pt is point, confusing sorry
	}
	
	vpNpos[pf] = to;
	//apply lambda function to all sub of 1st argument 
	sub_apply(pf->data, [&](const MindNode& sp) {
		for(auto& [vp, pos] : vpNpos) //if sub & not clogged together
			if(vp->data == sp && abs(pos - from) > 20) pos += to - from;//parallel move
	});
	pf->data->pt = parent ? to - vpNpos[parent] : 0;
	//std::cout << a.second << ' ' << a.first->data->pt << std::endl;
	generate_graph();
}

void popup(V* v);
void GraphView::right_click(Point pt) 
{///popup to configure node
	if(V* v = pick(pt)) {
		popup(v);
		generate_graph();
	}
}

std::vector<std::shared_ptr<Drawable>>::const_iterator GraphView::begin() const 
{
	return drawables_.begin();
}

std::vector<std::shared_ptr<Drawable>>::const_iterator GraphView::end() const 
{
	return drawables_.end();
}

void GraphView::cutNpaste(V* from, V* to) 
{///cut an edge from 'from' paste to 'to'
	///deal with path
	string from_path = from->data->path;
	string to_path = to->data->path + to->data->name + '/';
	from->data->path = to_path;
	sub_apply(from->data, [&](MindNode& sp) {
			sp->path.replace(sp->path.find(from_path), from_path.size(), to_path);});

	///deal with edge
	V* parent = get_parent(from);
	E* tmp;
	for(E* e = parent->edge, *prev = e; e; prev = e, e = e->edge) {//cut edge
		if(e->vertex == from) {
			tmp = e;
			if(e != parent->edge) prev->edge = e->edge;
			else parent->edge = e->edge;
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

	///change one arrow
	for(auto& a : arrows_) 
		if(get<0>(a) == parent && get<1>(a) == from) get<0>(a) = to;
}

void GraphView::generate_graph() 
{
	drawables_.clear();
	for(auto& a : arrows_) {//reconfigure arrows tip positions according to vertex
		V* v = std::get<1>(a);//position
		if(!v->data->show) continue;
		auto d1 = vpNpos[std::get<0>(a)];//starting point
		auto d2 = vpNpos[v];//ending point
		auto d3 = CIRCLE_SIZE * (d2 - d1) / abs(d2 - d1);
		d1 += d3;//make arrow stop before circle
		d2 -= d3;
		Arrow arrow{d1, d2, 1};
	//	arrow.txt(std::get<2>(a));//show weight
		//if(std::get<3>(a)) arrow.set_rgb(0,0,1);//if v is marked
		auto sp = std::get<1>(a)->data;
		arrow.set_rgba((double)sp->color[1][0] / 255, (double)sp->color[1][1] / 255, 
				(double)sp->color[1][2] / 255, (double)sp->color[1][3] / 255);
		drawables_.push_back(std::make_shared<Arrow>(arrow));
	}
	for(auto& a : vpNpos) {//draw nodes according to shape of data
		int h = CIRCLE_SIZE / 2;//vpNpos : vertex_pointer & position
		auto sp = a.first->data;//shared_pointer of mindnode
		if(!sp->show) continue;
		int w = sp->name.size() * CIRCLE_SIZE / 10;//approximate width
		w = std::max(w, h);
		if(sp->width && sp->height) {//if node has predefined width and height
			w = sp->width / 2;
			h = sp->height / 2;
		}

		Drawable* dr;
		auto s = a.second - Point{w, h};
		auto e = a.second + Point{w, h};
		switch(sp->outline) {
			case MindNode::Ellipse: dr = new Ellipse{s, e}; break;
			case MindNode::Rect: 	dr = new Box{s, e}; break;
			case MindNode::Diamond: dr = new Diamond{s, e}; break;
			case MindNode::Picture: dr = new Pix{sp->path + sp->name, s, e}; 
		}
		
		dr->txt(sp->name);
		dr->set_rgb((double)sp->color[0][0] / 255, (double)sp->color[0][1] / 255, 
					(double)sp->color[0][2] / 255);
		dr->set_rgba((double)sp->color[2][0] / 255, (double)sp->color[2][1] / 255, 
					(double)sp->color[2][2] / 255, (double)sp->color[2][3] / 255);
		drawables_.push_back(shared_ptr<Drawable>{dr});
	}
}

V* GraphView::pick(Point p) 
{//returns a V* at that position, if none return null
	for(auto& a : vpNpos) 
		if(abs(a.second - p)<20 && a.first->data->show) return a.first;
	return nullptr;
}
