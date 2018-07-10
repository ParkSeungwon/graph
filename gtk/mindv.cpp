#include<gtkmm.h>
#include"sketch.h"
#include"graphview.h"
#include"src/parsetree.h"
#include"src/mindnode.h"
using namespace std;

int main(int c, char** av)
{
	if(c < 2) return 0;

	int i=0;
	auto app = Gtk::Application::create(i, av);
	Win win;
	win.set_title("File Browser inspired by MindMap");
	win.show_all_children();
	return app->run(win);
}


