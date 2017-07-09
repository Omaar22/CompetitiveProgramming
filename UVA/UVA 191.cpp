/*
	author: omar22
	idea: brute force for each vertical line in the rectangle check if it intersects with the line
 */

#include <bits/stdc++.h>

using namespace std;

typedef complex<double> point;
const double EPS = 1e-11;
#define cp(a, b)                 ( (conj(a)*(b)).imag() )    // a*b sin(T), if zero -> parllel
int ccw(point a, point b, point c) {
	point v1(b - a), v2(c - a);
	double t = cp(v1, v2);
	
	if (t > +EPS)
		return +1;
	if (t < -EPS)
		return -1;
	if (v1.real() * v2.real() < -EPS || v1.imag() * v2.imag() < -EPS)
		return -1;
	if (norm(v1) < norm(v2) - EPS)
		return +1;
	return 0;
}

bool intersect(point p1, point p2, point p3, point p4) {
	// special case handling if a segment is just a point
	bool x = (p1 == p2), y = (p3 == p4);
	if (x && y) return p1 == p3;
	if (x) return ccw(p3, p4, p1) == 0;
	if (y) return ccw(p1, p2, p3) == 0;
	
	return ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
		   ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d", &t);
	while (t--) {
		point p0, p1;
		int minX = 2e9, minY = 2e9, maxX = -2e9, maxY = -2e9;
		for (int i = 0; i < 4; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			if (i == 0) {
				p0 = {x, y};
			} else if (i == 1) {
				p1 = {x, y};
			} else {
				minX = min(minX, x);
				minY = min(minY, y);
				maxX = max(maxX, x);
				maxY = max(maxY, y);
			}
		}
		bool T = false;
		for (int x = minX; x <= maxX; ++x) {
			if (intersect(p0, p1, point(x, minY), point(x, maxY))) {
				T = true;
				break;
			}
		}
		if (T)
			puts("T");
		else
			puts("F");
	}
	return 0;
}
