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

MindNode::MindNode() {}
MindNode::MindNode(string fname, MindNode::Type type)
{
	full_path = fname;
	name = full_path.substr(0, full_path.rfind('/'));
	this->type = type;
	show = type == Dir ? true : false;
	for(int i=0; i<3; i++) for(int j=0; j<4; j++) color[i][j] = 255;
	switch(type) {
		case Dir: outline = Ellipse; break;
		case Virtual: color[2][3] = 0;//transparent shape color
		case File: outline = Rect; break;
	}
	width = name.size() * 10;
	height = 30;
}

bool MindNode::operator==(const MindNode& r) 
{
	return full_path == r.full_path;
}

istream& operator>>(istream& is, MindNode& r) {
	Json::Value jv;
	is >> jv;
	r.full_path = jv["full path"].asString();
	r.name = jv["name"].asString();
	r.show = jv["show"].asBool();
	r.shrink = jv["shrink"].asBool();
	r.line = jv["Line"].asString() == "direct" ? MindNode::Line::Direct : MindNode::Line::Plant;
	r.type = static_cast<MindNode::Type>(jv["Type"].asInt());
	r.outline = static_cast<MindNode::Shape>(jv["Shape"].asInt());
	for(int i=0; i<3; i++) for(int j=0; j<4; j++) r.color[i][j] = jv["color"][i][j].asInt();
	r.width = jv["width"].asInt();
	r.height = jv["height"].asInt();
	r.tooltip = jv["tooltip"].asString();
	return is;
}

ostream& operator<<(ostream& o, const MindNode& node)
{
	Json::Value jv;
	jv["full path"] = node.full_path;
	jv["name"] = node.name;
	jv["show"] = node.show;
	jv["shrink"] = node.shrink;
	jv["Line"] = node.line == MindNode::Line::Direct ? "direct" : "plant";
	jv["Type"] = static_cast<int>(node.type);
	jv["Shape"] = static_cast<int>(node.outline);
	for(int i=0; i<3; i++) for(int j=0; j<4; j++) jv["color"][i][j] = node.color[i][j];
	jv["tooltip"] = node.tooltip;
	jv["width"] = node.width;
	jv["height"] = node.height;

	o << jv;
	return o;
}

