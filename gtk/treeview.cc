#include<gtkmm.h>
#include<iostream>
#include"drawable.h"
#include"treeview.h"
#include"graphv.h"
#include"tgraph.h"
using namespace std;

GraphView<Vertex<const char*>, Edge<const char*>, const char*>* pgv;
GraphView<Vertex<int>, Edge<int>, int>* tgv;

Win::Win() 
{
	add(scwin_);
	scwin_.add(sketch_);
	set_default_size(1000, 900);
	show_all_children();
}

SketchBook::SketchBook()
{
	set_size_request(1000, 1000);
	add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
	tgv->drag({700, 500}, {900, 500});
}

bool SketchBook::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) 
{
	for(auto& a : *pgv) (*a)(cr);
	for(auto& a : *tgv) (*a)(cr);
	return true;
}

void SketchBook::refresh()
{
	auto win = get_window();
    if (win)  {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
}

bool SketchBook::on_button_press_event(GdkEventButton* e)
{
	x = e->x;
	y = e->y;
	return false;
}
bool Win::on_button_press_event(GdkEventButton* e)
{
	cout << e->x << ' ' << e->y << endl;
	return true;
}

bool SketchBook::on_button_release_event(GdkEventButton* e)
{
	tx = e->x;
	ty = e->y;
	pgv->drag({x, y}, {tx, ty});
	tgv->drag({x, y}, {tx, ty});
	refresh();	
	return true;
}

