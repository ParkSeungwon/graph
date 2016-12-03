#pragma once
#include<vector>
class Drawable;
class SketchBook : public Gtk::DrawingArea
{
public:
	SketchBook();
	void draw(std::shared_ptr<Drawable> to_draw);

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	bool on_button_press_event(GdkEventButton* e);
	bool on_button_release_event(GdkEventButton* e);
	std::vector<std::shared_ptr<Drawable>> to_draws_; 

private:
	void refresh();
	int x, y, tx, ty;
};

class Win : public Gtk::Window
{
public:
	Win();
	void draw(std::shared_ptr<Drawable> to_draw);

protected:
	Gtk::ScrolledWindow scwin_;
	SketchBook sketch_;
};

