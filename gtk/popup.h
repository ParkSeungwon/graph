#include<gtkmm.h>
#include"mindmap.h"

class AttributeDialog : public Gtk::Dialog
{///Popup window to set the attributes of a MindNode
public:
	AttributeDialog();
	Gtk::RadioButton *outline_bts[4], *line_bts[2];
	Gtk::Label lb;
	Gtk::Entry name;

protected:
	Gtk::RadioButton::Group outline, line;
	Gtk::RadioButton Circle, Rect, Diamond, Ellipse;
	Gtk::RadioButton Plant, Direct;
	Gtk::Box* vb;
	Gtk::HBox hb1, hb2;
};

void popup(Vertex<std::shared_ptr<MindNode>>* v);

template<typename T> 
void sub_width_apply(Vertex<std::shared_ptr<MindNode>>* v, T func) 
{
	for(auto* e = v->edge; e; e = e->edge) {
		func(e->vertex->data);
		if(e->vertex->data->type == MindNode::Dir) 
			sub_width_apply(e->vertex, func);
	}
}
	
