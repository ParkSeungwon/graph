#pragma once
#include<vector>
#include<memory>
#include"graphv.h"

class MindNode;
class SketchBook : public Gtk::DrawingArea
{
public:
	SketchBook(Graph<std::shared_ptr<MindNode>>& graph);

protected:
	GraphV<std::shared_ptr<MindNode>> gv_;
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
	Win(Graph<std::shared_ptr<MindNode>>& graph);

protected:
	bool on_button_press_event(GdkEventButton* e);
	Gtk::ScrolledWindow scwin_;
	SketchBook sketch_;
};

