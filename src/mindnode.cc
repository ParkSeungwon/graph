#include<map>
#include<dirent.h>
#include<sstream>
#include<iostream>
#include<cctype>
#include"json/json.h"
#include"mindnode.h"
using namespace std;

Point::Point(int x, int y) : complex<double>(x, y) {}
Point::Point(complex<double> im) : complex<double>(im) {}
int Point::x() const {return real();}
int Point::y() const {return imag();}

MindNode::MindNode(string fname, MindNode::Type type)
{
	name = fname;
	this->type = type;
	show = type == Dir ? true : false;
	for(int i=0; i<3; i++) color[i][3] = 255;
	switch(type) {
		case Dir: outline = Ellipse; break;
		case Virtual: color[2][3] = 0;//transparent shape color
		case File: outline = Rect; break;
	}
}

bool MindNode::operator==(const MindNode& r) 
{
	return full_path == r.full_path;
}

istream& operator>>(istream& is, MindNode& r) {
	Json::Value jv;
	is >> jv;
	r.full_path = jv["full path"];
	r.name = jv["name"];
	r.show = jv["show"];
	r.shrink = jv["shrink"];
	r.pt = {jv["point"][0], jv["point"][1]};
	r.Line = jv["Line"] == "direct" ? MindNode::Line::Direct : MindNode::Line::Plant;
	r.Type = static_cast<MindNode::Type>(jv["Type"]);
	r.Shape = static_cast<MindNode::Shape>(jv["Shape"]);
	for(int i=0; i<3; i++) for(int j=0; j<4; j++) r.color[i][j] = jv["color"][i][j];
	r.width = jv["width"];
	r.height = jv["height"];
	r.tooltip = jv["tooltip"]
	return is;
}

ostream& operator<<(ostream& o, const MindNode& node)
{
	Json::Value jv;
	jv["full path"] = node.full_path;
	jv["name"] = node.name;
	jv["show"] = node.show;
	jv["shrink"] = node.shrink;
	Json::Value pt;
	pt[0] = node.pt.x();
	pt[1] = node.pt.y();
	jv["point"] = pt;
	jv["Line"] = node.Line == MindNode::Line::Direct ? "direct" : "plant";
	jv["Type"] = static_cast<int>(node.Type);
	jv["Shape"] = static_cast<int>(node.Shape);
	Json::Value col;
	for(int i=0; i<3; i++) {
		Json::Value c;
		for(int j=0; j<4; j++) c[i] = node.colors[i][j];
		col[i] = c;
	}
	jv["color"] = col;
	jv["tooltip"] = node.tooltip;
	jv["width"] = node.width;
	jv["height"] = node.height;

	o << jv;
	return o;
}
