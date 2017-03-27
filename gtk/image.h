#include"drawable.h"

class Pix : public Box
{
public:
	Pix(std::string filename, Point s, Point e);
	virtual void operator()(const Cairo::RefPtr<Cairo::Context>& cr) override;

protected:
	std::string filename;
	Point start, end;
	bool initialized = false;
};

