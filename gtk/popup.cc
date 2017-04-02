#include"popup.h"
using namespace std;
using namespace Gtk;

AttributeDialog::AttributeDialog() : Picture(outline, "picture"), 
	Rect(outline, "rect"), Diamond(outline, "diamond"), Ellipse(outline, "ellipse"), 
	Plant(line, "plant"), Direct(line, "direct"), lb("Test")
{
	set_size_request(100,100);
	vb = get_content_area();
	vb->pack_start(name);
	vb->pack_start(hb1);
	vb->pack_start(hb2);
	hb1.pack_start(Picture, PACK_SHRINK);
	hb1.pack_start(Rect, PACK_SHRINK);
	hb1.pack_start(Diamond, PACK_SHRINK);
	hb1.pack_start(Ellipse, PACK_SHRINK);
	hb2.pack_start(Plant, PACK_SHRINK);
	hb2.pack_start(Direct, PACK_SHRINK);
	add_button("_Ok", 1);
	add_button("_Cancel", 0);
	outline_bts[0] = &Picture;
	outline_bts[1] = &Rect;
	outline_bts[2] = &Diamond;
	outline_bts[3] = &Ellipse;
	line_bts[0] = &Plant;
	line_bts[1] = &Direct;
	show_all_children();
}

ResizeDialog::ResizeDialog() : fixed_ratio("fix rate"), wl("width"), hl("height"),
	width(Gtk::Adjustment::create(1, 0, 1000, 1, 10, 0)), 
	height(Gtk::Adjustment::create(1, 0, 1000, 1, 10, 0))
{
	set_size_request(100, 100);
	Gtk::Box* box = get_content_area();
	box->pack_start(fixed_ratio, PACK_SHRINK);
	whb.pack_start(wl, PACK_SHRINK);
	whb.pack_end(width, PACK_SHRINK);
	hhb.pack_start(hl, PACK_SHRINK);
	hhb.pack_end(height, PACK_SHRINK);
	box->pack_start(whb, PACK_SHRINK);
	box->pack_start(hhb, PACK_SHRINK);
	width.set_numeric();
	height.set_numeric();
	width.signal_value_changed().connect(bind(&ResizeDialog::on_change, this, 'w'));
	height.signal_value_changed().connect(bind(&ResizeDialog::on_change, this, 'h'));
	fixed_ratio.signal_toggled().connect(bind(&ResizeDialog::on_toggle, this));
	add_button("_Ok", 1);
	add_button("_Cancel", 0);
	show_all_children();
}

void ResizeDialog::on_change(char c) 
{
	if(fixed_ratio.get_active()) {
		switch(c) {
			case 'w': height.set_value(width.get_value() / rate); break;
			case 'h': width.set_value(rate * height.get_value()); break;
		}
	}
}

void ResizeDialog::on_toggle()
{
	if(fixed_ratio.get_active()) rate = width.get_value() / height.get_value();
}
		

static void shape_chooser(Vertex<shared_ptr<MindNode>>* v) {
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
				string command = "mv '";
				command += mn->path + mn->name + "' '" + mn->path + ad.name.get_text() + "'";
				system(command.data());
				mn->name = ad.name.get_text();
			}
		}
	}
}

static int color_chooser(Vertex<shared_ptr<MindNode>>* v) {
	int result;
	{
		Gtk::Dialog dia;
		dia.add_button("_Text",1);
		dia.add_button("_Line",2);
		dia.add_button("_Shape",3);
		dia.add_button("Cancel",0);
		result = dia.run();
	}
	if(0 < result && result < 4) {
		Gtk::ColorChooserDialog dia;
		if(dia.run() == Gtk::RESPONSE_OK) {
			auto color = dia.get_rgba();
			v->data->color[result-1][0] = color.get_red() * 255;
			v->data->color[result-1][1] = color.get_green() * 255;
			v->data->color[result-1][2] = color.get_blue() * 255;
			v->data->color[result-1][3] = color.get_alpha() * 255;
		}
	}
}

static void app_chooser(Vertex<shared_ptr<MindNode>>* v) {
	string file = v->data->name;
	string ext = file.substr(file.rfind('.') + 1);
	
	const char* extensions[] = {"pdf", "png", "jpg", "gif", "JPG", "xpm"};
	const char* programs[] = {"nautilus ", "evince ", "gthumb ", "gedit "};

	int i=0;
	while(ext != extensions[i] && i < 6) i++;
	
	string command;
	
	if(v->data->type == MindNode::Dir) command = programs[0];
	else if(!i) command = programs[1];
	else if(i < 6) command = programs[2];
	else command = programs[3];
	
	command += v->data->path + "'" + file + "'&";
	system(command.data());
}

static void file_chooser(Vertex<shared_ptr<MindNode>>* v) {
	Gtk::FileChooserDialog dia("Choose files to expose or unexpose");
	dia.set_select_multiple();
	dia.set_current_folder(v->data->path + v->data->name);
	dia.add_button("_Ok", 1);
	dia.add_button("_Cancel", 0);
	if(dia.run() == 1) {
		string s = dia.get_filename();
		for(Edge<shared_ptr<MindNode>>* e = v->edge; e; e = e->edge)
			if(e->vertex->data->name == s.substr(s.rfind('/')+1))
				e->vertex->data->show = !e->vertex->data->show;
	}
}

static void resize(Vertex<shared_ptr<MindNode>>* v) {
	ResizeDialog dia;
	dia.width.set_value(v->data->width);
	dia.height.set_value(v->data->height);
	if(dia.run()) {
		v->data->width = dia.width.get_value_as_int();
		v->data->height = dia.height.get_value_as_int();
	}
}

void popup(Vertex<shared_ptr<MindNode>>* v) {
	int result;
	{
		Gtk::Dialog dia("Selelct one");
		dia.add_button("_Shape",1);
		dia.add_button("_Color",2);
		dia.add_button("_Open",3);
		dia.add_button("_Resize",4);
		if(v->data->type == MindNode::Dir) dia.add_button("_Expose", 5);
		dia.add_button("Cancel",0);
		result = dia.run();
	}

	switch(result) {
		case 1: shape_chooser(v); break;
		case 2: color_chooser(v); break;
		case 3: app_chooser(v); break;
		case 4: resize(v); break;
		case 5: file_chooser(v); break;
		default:;
	}
}
