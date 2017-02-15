#include<gtkmm.h>
#include<iostream>
#include"drawable.h"
#include"treeview.h"
#include"graphv.h"
#include"src/parsetree.h"
using namespace std;

GraphV<char>* pv;
bool SketchBook::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) 
{
	for(auto& a : *pv) (*a)(cr);
	return true;
}

template <typename T> void SketchBook::draw(Graph<T> gr)
{
	
bool SketchBook::on_button_release_event(GdkEventButton* e)
{
	tx = e->x;
	ty = e->y;
	pv->drag({x, y}, {tx, ty});
	refresh();	
	return true;
}

Win::Win() 
{
	add(scwin_);
	scwin_.add(sketch_);
	set_default_size(1000, 900);
	show_all_children();
}

SketchBook::SketchBook()
{
	set_size_request(5000, 5000);
	add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
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

ostream& operator<<(ostream& o, const array<int, 5>& r)
{
	for(auto& a : r) o << a << ',';
	return o;
}
