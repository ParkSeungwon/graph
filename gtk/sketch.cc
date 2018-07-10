#include<gtkmm.h>
#include<iostream>
#include"drawable.h"
#include"sketch.h"
#include"src/mindnode.h"
#include"src/graph.h"
#include"src/parsetree.h"
using namespace std;

SketchBook::SketchBook(string s) : gv_{s}
{
	set_size_request(5000, 5000);
	add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
}

bool SketchBook::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) 
{
	for(auto& a : gv_) (*a)(cr);
	return true;
}

bool SketchBook::on_button_release_event(GdkEventButton* e)
{
	if(e->button == 1) {
		tx = e->x;
		ty = e->y;
		gv_.drag({x, y}, {tx, ty});
		refresh();	
		return true;//does not propagate
	}
	return false;//propagate
}
bool SketchBook::on_button_press_event(GdkEventButton* e)
{
	if(e->button == 1) {
		x = e->x;
		y = e->y;
		return true;//does not propagate
	} else if(e->button == 3) gv_.right_click({e->x, e->y});
	return false;//propagate
}
bool Win::on_button_press_event(GdkEventButton* e)
{
	cout << e->x << ' ' << e->y << endl;
	return true;
}
Win::Win(string s) : sketch_{s}
{
	add(scwin_);
	scwin_.add(sketch_);
//	add(sketch_);
	set_default_size(1000, 900);
	show_all_children();
}

void SketchBook::refresh()
{
	auto win = get_window();
    if (win)  {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
}


ostream& operator<<(ostream& o, const array<int, 5>& r)
{
	for(auto& a : r) o << a << ',';
	return o;
}
