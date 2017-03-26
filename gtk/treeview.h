#pragma once
#include<vector>
#include"tgraph.h"

class Drawable;
class SketchBook : public Gtk::DrawingArea
{
public:
	SketchBook();
	template <typename T> void draw(Graph<T> gr);

protected:
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
	Gtk::VBox vb_;
	Win();

protected:
	bool on_button_press_event(GdkEventButton* e);
	Gtk::ScrolledWindow scwin_;
	SketchBook sketch_;
};

