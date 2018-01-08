#pragma once
#include<vector>
#include<memory>

class Drawable;
class MindNode;
template <class T> class GraphV;
class SketchBook : public Gtk::DrawingArea
{
public:
	SketchBook(GraphV<std::shared_ptr<MindNode>>*);

protected:
	GraphV<std::shared_ptr<MindNode>>* p_drawables_;
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	bool on_button_press_event(GdkEventButton* e);
	bool on_button_release_event(GdkEventButton* e);

private:
	void refresh();
	int x, y, tx, ty;
};

class Win : public Gtk::Window
{
public:
	Win(GraphV<std::shared_ptr<MindNode>>*);

protected:
	bool on_button_press_event(GdkEventButton* e);
	Gtk::ScrolledWindow scwin_;
	SketchBook sketch_;
};

