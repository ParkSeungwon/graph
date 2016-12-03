#include<complex>
#include"drawable.h"
using namespace std;

Point::Point(int x, int y) : complex<double>(x, y) {}
Point::Point(complex<double> im) : complex<double>(im) {}
int Point::x() const {return real();}
int Point::y() const {return imag();}
void Drawable::set_rgb(double r, double g, double b) { r_ = r; g_ = g; b_ = b; } 
void Drawable::line_width(int w) { line_width_ = w; }
void Drawable::operator()(const Cairo::RefPtr<Cairo::Context>& cr) 
{
	cr->save();
	Point p{(start_ + end_) / 2.0};
	if(txt_ != "") {
		cr->set_source_rgba(r_, g_, b_, 0.5);
		auto layout = Pango::Layout::create(cr);
		layout->set_font_description(font_);
		layout->set_text(txt_);
		int text_width, text_height;
		layout->get_pixel_size(text_width, text_height);
		cr->move_to(p.x() - text_width / 2, p.y() - text_height / 2);
		layout->show_in_cairo_context(cr);
	}
	cr->restore();
}
void Drawable::set_size(int sz)
{
	font_.set_size(sz);
}
void Drawable::set_weight(int weight)//100, 200, ... ~ 1000
{
	font_.set_weight(static_cast<Pango::Weight>(weight));
}
void Drawable::set_family(string f)
{
	font_.set_family(f);
}


Line::Line() {}
Line::Line(initializer_list<Point> li)
{
	points_ = li;
	start_ = points_[0];
	end_ = points_[1];
}
void Line::operator()(const Cairo::RefPtr<Cairo::Context>& cr) 
{
	Drawable::operator()(cr);
	cr->save();
	cr->set_source_rgba(r_, g_, b_, 0.5);
	cr->set_line_width(line_width_);
	cr->move_to(points_[0].x(), points_[0].y());
	for(auto& a : points_) cr->line_to(a.x(), a.y());
	cr->stroke();
	cr->restore();
}

Arrow::Arrow(Point s, Point e, int tip) 
{
	start_ = s;
	end_ = e;
	points_.push_back(s);
	if(tip > 1) {
		auto angle = arg(e - s);
		auto im1 = polar(10.0, angle - M_PI / 8);
		auto im2 = polar(10.0, angle + M_PI / 8);
		points_.push_back(s + im1);
		points_.push_back(s + im2);
		points_.push_back(s);
	}
	points_.push_back(e);
	if(tip > 0) {
		auto angle = arg(s - e);
		auto im1 = polar(10.0, angle - M_PI / 8);
		auto im2 = polar(10.0, angle + M_PI / 8);
		points_.push_back(e + im1);
		points_.push_back(e + im2);
		points_.push_back(e);
	}
}

Box::Box(Point s, Point e)
{
	start_ = s;
	end_ = e;
	Point a{s.x(), e.y()};
	Point b{e.x(), s.y()};
	points_.push_back(s);
	points_.push_back(a);
	points_.push_back(e);
	points_.push_back(b);
	points_.push_back(s);
}

Ellipse::Ellipse(Point s, Point e)
{
	start_ = s;
	end_ = e;
}
void Ellipse::operator()(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Drawable::operator()(cr);
	Point c{(start_ + end_) / 2.0};
	int w = abs(start_.x() - end_.x());
	int h = abs(start_.y() - end_.y());
	cr->save();
	cr->set_source_rgba(r_, g_, b_, 0.5);
	cr->set_line_width(line_width_);
	cr->begin_new_sub_path();//to avoid trailing line
	cr->translate(c.x(), c.y());
	cr->scale(1.0, (double)h/w);
	cr->arc(0, 0, w, 0, 2 * M_PI);
	cr->stroke();
	cr->restore();
}



