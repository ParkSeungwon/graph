#include"image.h"
using namespace std;

Pix::Pix(string file, Point s, Point e) : Box(s - Point{3,3}, e + Point{3,3})
{
	start = s; end = e;
	filename = file;
}

void Pix::operator()(const Cairo::RefPtr<Cairo::Context>& cr) 
{///limited gtk dependency inside of this function
	if(!initialized) {
		Point im = end - start;//width + i * height
		image = Gdk::Pixbuf::create_from_file(filename);
		w = im.x();
		h = im.y();
		image = image->scale_simple(w, h, Gdk::INTERP_BILINEAR);
		initialized = true;
	}
	Box::operator()(cr);
	Gdk::Cairo::set_source_pixbuf(cr, image, start.x(), start.y());//anchor source
	cr->rectangle(start.x(), start.y(), w, h);					//at position x, y
	cr->fill();
}
		
