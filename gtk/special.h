#include<memory>
#include"graphv.h"
#include"mindmap.h"
#include"image.h"
#include"popup.h"
typedef Vertex<std::shared_ptr<MindNode>> V;
typedef Edge<std::shared_ptr<MindNode>> E;

template<> class GraphView<V, E, std::shared_ptr<MindNode>> 
{//template specialization for MindNode
public:
	GraphView(V* gr);
	virtual ~GraphView();
	void allocate_node(V* vt);
	V* get_parent(V* s); 
	virtual void drag(Point from, Point to);
	virtual void right_click(Point pt);	
	std::vector<std::shared_ptr<Drawable>>::const_iterator begin() const;	
	std::vector<std::shared_ptr<Drawable>>::const_iterator end() const;	
	void treeview(int height);

protected:
	V* root = nullptr;
	std::map<V*, Point> vpNpos;
	std::vector<std::tuple<V*, V*, int, int>> arrows_;//from,to,weight,v
	std::vector<std::shared_ptr<Drawable>> drawables_;//vpNpos,arrows_->drawables

private:
	int width_;

	template<typename T> void width_apply(V* p, T func) {
		for(auto* e = p->edge; e; e = e->edge) {
			func(e->vertex->data);
			if(e->vertex->data->type == MindNode::Dir) width_apply(e->vertex, func);
		}
	}

	void cutNpaste(V* from, V* to);
	void treeview(V* p, int x, int y, int h);
	void generate_graph();
};
