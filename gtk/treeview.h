#pragma once
#include<vector>
class Drawable;
template<typename T> class SketchBook : public Gtk::DrawingArea
{
public:
	SketchBook(T& p) : pgv(p) {
		set_size_request(3000, 1000);
		add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
	}

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
		for(auto& a : pgv) (*a)(cr);
		return true;
	}
	bool on_button_press_event(GdkEventButton* e) {
		x = e->x;
		y = e->y;
		return true;
	}
	bool on_button_release_event(GdkEventButton* e) {
		tx = e->x;
		ty = e->y;
		pgv.drag({x, y}, {tx, ty});
		refresh();	
		return true;
	}

private:
	T& pgv;
	void refresh() {
		auto win = get_window();
		if (win)  {
			Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
			win->invalidate_rect(r, false);
		}
	}

	int x, y, tx, ty;
};

template<typename T> class Win : public Gtk::Window
{
public:
	Win(T t) : sketch_(t) {
		add(scwin_);
		scwin_.add(sketch_);
		set_default_size(1500, 900);
		show_all_children();
	}
	
protected:
	Gtk::ScrolledWindow scwin_;
	SketchBook<T> sketch_;
};

