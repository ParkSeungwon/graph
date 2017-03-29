#include"popup.h"
using namespace std;
using namespace Gtk;

AttributeDialog::AttributeDialog() : Circle(outline, "circle"), 
	Rect(outline, "rect"), Diamond(outline, "diamond"), Ellipse(outline, "ellipse"), 
	Plant(line, "plant"), Direct(line, "direct"), lb("Test")
{
	set_size_request(100,100);
	vb = get_content_area();
	vb->pack_start(lb);
	vb->pack_start(hb1);
	vb->pack_start(hb2);
	hb1.pack_start(Circle, PACK_SHRINK);
	hb1.pack_start(Rect, PACK_SHRINK);
	hb1.pack_start(Diamond, PACK_SHRINK);
	hb1.pack_start(Ellipse, PACK_SHRINK);
	hb2.pack_start(Plant, PACK_SHRINK);
	hb2.pack_start(Direct, PACK_SHRINK);
	add_button("_Ok", 1);
	add_button("_Cancel", 2);
	show_all_children();
}

MindNode popup(MindNode mn) {
	AttributeDialog ad;
	int result = ad.run();
	if(result == 1) {
	}
	return mn;
}


