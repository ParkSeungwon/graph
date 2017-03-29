#include<gtkmm.h>
#include"mindmap.h"

class AttributeDialog : public Gtk::Dialog
{///sets the attributes of a node
public:
	AttributeDialog();

protected:
	Gtk::Label lb;
	Gtk::RadioButton::Group outline, line;
	Gtk::RadioButton Circle, Rect, Diamond, Ellipse;
	Gtk::RadioButton Plant, Direct;
	Gtk::Box* vb;
	Gtk::HBox hb1, hb2;
};

MindNode popup(MindNode);
