#ifndef EX2_POINT_IMPL
#define EX2_POINT_IMPL
#include "C:\Git\AdvancedTopicsInProgramming\Ex2\Point.h"
class PointImpl :
	public Point
{
public:
	PointImpl(int x, int y) :x(x), y(y) {}
	PointImpl(const Point& p) :x(p.getX()), y(p.getY()) {}
	~PointImpl() = default;
	int getX() const override { return x; }
	int getY() const override { return y; }
private:
	const int x;
	const int y;
};
#endif
