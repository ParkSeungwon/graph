#include<memory>
#include"src/mindnode.h"
#include"src/graph.h"
#include"image.h"
typedef Vertex<MindNode> V;
typedef Edge<MindNode> E;

class GraphView : public Graph<MindNode>
{//template specialization for MindNode
public:
	Graphview();
	virtual ~GraphView();
	void generate_drawables(V* from);
	virtual void drag(Point from, Point to);
	virtual void right_click(Point pt);	
	std::vector<std::shared_ptr<Drawable>>::const_iterator begin() const;	
	std::vector<std::shared_ptr<Drawable>>::const_iterator end() const;	

protected:
	V* root = nullptr;
	std::map<V*, Point> vpNpos;//vertex pointer & absolute drawing position of that vertex 
	std::vector<std::tuple<V*, V*, int, int>> arrows_;//from,to,weight,v
	std::vector<std::shared_ptr<Drawable>> drawables_;//vpNpos,arrows_->drawables

private:
	int width_;

	void allocate_node(V* vt);
	void cutNpaste(V* from, V* to);
	void treeview(V* p, int x, int y, int h);
	void generate_graph();
	V* pick(Point p);
};
