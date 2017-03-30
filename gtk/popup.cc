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

void popup(Vertex<shared_ptr<MindNode>>* v) {
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
		if(mn->name != ad.name.get_text()) {
			for(auto* e = v->edge; e; e = e->edge) 
				if(e->vertex->data->name == ad.name.get_text()) same_name = true;
			if(!same_name) {
				char command[200] = "mv ";
				strcat(command, mn->path.data());
				strcat(command, mn->name.data());
				strcat(command, " ");
				strcat(command, mn->path.data());
				strcat(command, ad.name.get_text().data());
				system(command);
				mn->name = ad.name.get_text();
			}
		}
	}
}


