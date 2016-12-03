#include<gtkmm.h>
#include<iostream>
#include"drawable.h"
#include"treeview.h"
#include"graphv.h"
#include"tgraph.h"
using namespace std;

GraphView<Vertex<int>, Edge<int>, int>* pgv;

Win::Win() 
{
	add(scwin_);
	scwin_.add(sketch_);
	set_default_size(1500, 900);
	show_all_children();
}

void Win::draw(shared_ptr<Drawable> dr)
{
	sketch_.draw(dr);
}

void SketchBook::draw(shared_ptr<Drawable> d)
{
	to_draws_.push_back(d);
}
SketchBook::SketchBook()
{
	set_size_request(3000, 1000);
	add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
}

bool SketchBook::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) 
{
	for(auto& a : to_draws_) (*a)(cr);
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
	return true;
}

bool SketchBook::on_button_release_event(GdkEventButton* e)
{
	tx = e->x;
	ty = e->y;
	pgv->drag({x, y}, {tx, ty});
	to_draws_.clear();
	for(auto& a : *pgv) to_draws_.push_back(a);
	refresh();	
	return true;
}

