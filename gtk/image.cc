#include"image.h"
using namespace std;

Pix::Pix(string file, Point s, Point e) : Box(s - Point{3,3}, e + Point{3,3})
{
	start = s; end = e;
	filename = file;
}

void Pix::operator()(const Cairo::RefPtr<Cairo::Context>& cr) 
{///limited gtk dependency inside of this function
	static Glib::RefPtr<Gdk::Pixbuf> image;
	static Point im;
	if(!initialized) {
		im = end - start;//width + i * height
		image = Gdk::Pixbuf::create_from_file(filename);
		int w = image->get_width();
		int h = image->get_height();
		image = image->scale_simple(w, h, Gdk::INTERP_HYPER);
		initialized = true;
	}
	Box::operator()(cr);
	Gdk::Cairo::set_source_pixbuf(cr, image);//,im.x(),im.y()); 
	cr->rectangle(start.x(), start.y(), im.x(), im.y());
	cr->fill();
}
		
