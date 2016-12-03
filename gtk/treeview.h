#pragma once
#include<vector>
class Drawable;
class SketchBook : public Gtk::DrawingArea
{
public:
	SketchBook();

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
	Win();

protected:
	bool on_button_press_event(GdkEventButton* e);
	Gtk::ScrolledWindow scwin_;
	SketchBook sketch_;
};

