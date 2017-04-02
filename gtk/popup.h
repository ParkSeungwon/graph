#include<gtkmm.h>
#include"mindmap.h"

void popup(Vertex<std::shared_ptr<MindNode>>* v);

class AttributeDialog : public Gtk::Dialog
{///Popup window to set the attributes of a MindNode
public:
	AttributeDialog();
	Gtk::RadioButton *outline_bts[4], *line_bts[2];
	Gtk::Label lb;
	Gtk::Entry name;

protected:
	Gtk::RadioButton::Group outline, line;
	Gtk::RadioButton Picture, Rect, Diamond, Ellipse;
	Gtk::RadioButton Plant, Direct;
	Gtk::Box* vb;
	Gtk::HBox hb1, hb2;
};

class ResizeDialog : public Gtk::Dialog
{
public:
	ResizeDialog();
	Gtk::SpinButton width, height;
	Gtk::CheckButton fixed_ratio;

protected:
	Gtk::Label wl, hl;
	Gtk::HBox whb, hhb;
	void on_change(char c);
	void on_toggle();
	float rate;
};
