#include"graphv.h"
#include"popup.h"
using namespace std;
using namespace Gtk;

AttributeDialog::AttributeDialog() : Circle(outline, "circle"), 
	Rect(outline, "rect"), Diamond(outline, "diamond"), Ellipse(outline, "ellipse"), 
	Plant(line, "plant"), Direct(line, "direct"), lb("Test")
{
	set_size_request(100,100);
	vb = get_content_area();
	vb->pack_start(name);
	vb->pack_start(hb1);
	vb->pack_start(hb2);
	hb1.pack_start(Circle, PACK_SHRINK);
	hb1.pack_start(Rect, PACK_SHRINK);
	hb1.pack_start(Diamond, PACK_SHRINK);
	hb1.pack_start(Ellipse, PACK_SHRINK);
	hb2.pack_start(Plant, PACK_SHRINK);
	hb2.pack_start(Direct, PACK_SHRINK);
	add_button("_Ok", 1);
	add_button("_Cancel", 0);
	outline_bts[0] = &Circle;
	outline_bts[1] = &Rect;
	outline_bts[2] = &Diamond;
	outline_bts[3] = &Ellipse;
	line_bts[0] = &Plant;
	line_bts[1] = &Direct;
	show_all_children();
}

static void shape_chooser(Vertex<shared_ptr<MindNode>>* v) 
{
	auto mn = v->data;
	AttributeDialog ad;
	ad.name.set_text(mn->name);
	ad.outline_bts[mn->outline]->set_active();
	ad.line_bts[mn->line]->set_active();
	if(ad.run()) {
		for(int i=0; i<5; i++) if(ad.outline_bts[i]->get_active()) {
			mn->outline = static_cast<MindNode::Shape>(i);
			break;
		}
		for(int i=0; i<2; i++) if(ad.line_bts[i]->get_active()) {
			mn->line = static_cast<MindNode::Line>(i);
			break;
		}
		bool same_name = false;
		if(mn->name != ad.name.get_text()) {//if changed & no same name 
			for(auto* e = v->edge; e; e = e->edge) //is present in the directory
				if(e->vertex->data->name == ad.name.get_text()) same_name = true;
			if(!same_name) {//rename it
				string command = "mv ";
				command += mn->path + mn->name + ' ' + mn->path + ad.name.get_text();
				system(command.data());
				mn->name = ad.name.get_text();
			}
		}
	}
}

static void color_chooser(Vertex<shared_ptr<MindNode>>* v) 
{
	Gtk::ColorChooserDialog dia;
	if(dia.run() == Gtk::RESPONSE_OK) {
		auto color = dia.get_rgba();
		v->data->r = color.get_red() * 255;
		v->data->g = color.get_green() * 255;
		v->data->b = color.get_blue() * 255;
		v->data->a = color.get_alpha() * 255;
	}
}

static void app_chooser(Vertex<shared_ptr<MindNode>>* v) 
{
	const char* extensions[] = {"pdf", "png", "jpg", "gif", "JPG", "xpm"};
	const char* programs[] = {"nautilus ", "evince ", "gthumb ", "gedit "};

	string file = v->data->name;
	string ext = file.substr(file.rfind('.') + 1);
	int i=0;
	while(ext != extensions[i] && i < 6) i++;
	
	string command;
	if(v->data->type == MindNode::Dir) command = programs[0];
	else if(!i) command = programs[1];
	else if(i < 6) command = programs[2];
	else command = programs[3];
	command += v->data->path + file + '&';
	system(command.data());
}

extern GraphV<shared_ptr<MindNode>>* pv;
static Vertex<shared_ptr<MindNode>>* to_paste;
static void cut(Vertex<shared_ptr<MindNode>>* v) 
{
	to_paste = v;
}
static void paste(Vertex<shared_ptr<MindNode>>* v)
{
	bool paste_to_sub = false, same_name = false;
	sub_width_apply(v, [&paste_to_sub](shared_ptr<MindNode> sp) {
			if(sp == to_paste->data) paste_to_sub = true; });
	for(auto* e = v->edge; e; e = e->edge) 
		if(e->vertex->data->name == to_paste->data->name) same_name = true;
	if(!paste_to_sub && !same_name) {
		string command = "mv ";
		command += to_paste->data->path + to_paste->data->name + ' ';
		command += v->data->path + v->data->name;
		system(command.data());
		//main()
		//pv->cutNpaste(to_paste, v);
	}
}




void popup(Vertex<shared_ptr<MindNode>>* v) 
{
	int result;
	{
		Gtk::Dialog dia;
		dia.add_button("_Shape",1);
		dia.add_button("_Color",2);
		dia.add_button("_Open",3);
		dia.add_button("_Cut",4);
		dia.add_button("_Paste",5);
		dia.add_button("Cancel",0);
		result = dia.run();
	}

	switch(result) {
		case 1: shape_chooser(v); break;
		case 2: color_chooser(v); break;
		case 3: app_chooser(v); break;
		case 4: cut(v); break;
		case 5: paste(v); break;
		default:;
	}
}
