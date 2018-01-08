#include"tgraph.h"
#include"graphv.h"
#include<gtkmm.h>
using namespace std;

class Sk : public Gtk::DrawingArea
{
public:
	Sk(GraphV<string>* gr) : drawables_(gr) {}

protected:
	GraphV<string>* drawables_;
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
		for(auto& a : *drawables_) (*a)(cr);
		return true;
	}
};

int main(int ac, char** av)
{
	auto app = Gtk::Application::create(ac, av);
	Graph<string> gr;
	gr.read_file("a.txt");
	gr.dijkstra("Roc", "Kee");
	GraphV<string> view{gr.data()};
	Sk sk{&view};
	Gtk::Window win;
	win.add(sk);
	win.show_all_children();
	return app->run(win);
}


