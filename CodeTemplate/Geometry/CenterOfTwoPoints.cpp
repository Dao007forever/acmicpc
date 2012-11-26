/*
 * Find the center of a circle with radious R that p1p2 is the diameter
 */
Point Find_Center(Point p1, Point p2)
{
	Point p3, center, mid;
	double b, c, ang;
	p3.x = p2.x - p1.x;
	p3.y = p2.y - p1.y;
	mid.x = (p1.x + p2.x) / 2;
	mid.y = (p1.y + p2.y) / 2;
	b = dis(p1, mid);
	c = sqrt(R * R - b);
	if (fabs(p3.y) < eps)
	{
		center.x = mid.x;
		center.y = mid.y + c;
	}
	else
	{
		ang = atan(-p3.x / p3.y);
		center.x = mid.x + c * cos(ang);
		center.y = mid.y + c * sin(ang);
	}
	return center;
}
