#include<gtkmm.h>
#include<string>
#include<iostream>
using namespace std;
using namespace Gtk;

class Sketch : public DrawingArea
{
public:
	Sketch(string s) {
		image = Gdk::Pixbuf::create_from_file(s);
		image = image->scale_simple(300, 100, Gdk::INTERP_NEAREST);
		cout << image->get_width() << 'X' << image->get_height() << endl;
	}
protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
		Gdk::Cairo::set_source_pixbuf(cr, image, 0, 0);
		cr->rectangle(0, 0, 300, 100);
		cr->fill();
//		cr->paint();
		return true;
	}
	Glib::RefPtr<Gdk::Pixbuf> image;
};

class Win : public Window
{
public:
	Win(string s) : sketch(s) {
		add(sketch);
		sketch.show();
		show_all_children();
	}
protected:
	Sketch sketch;
};

int main(int ac, char** av)
{
	int i=0;
	auto app = Application::create(i, av);
	Win win(av[1]);
	return app->run(win);
}

