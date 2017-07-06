/*
	author: omar22
	idea: calculate intersection point
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 2e2 + 1;
const double EPS = 1e-9;

typedef complex<double> point;
#define cp(a, b)                 ( (conj(a)*(b)).imag() )    // a*b sin(T), if zero -> parallel
bool intersectSegments(point a, point b, point c, point d, point &intersect) {
	double d1 = cp(a - b, d - c), d2 = cp(a - c, d - c), d3 = cp(a - b, a - c);
	if (fabs(d1) < EPS)
		return false;  // Parallel || identical
	double t1 = d2 / d1;
	intersect = a + (b - a) * t1;
	return true;
}

bool isCollinear(point a, point b, point c) {
	return fabs(cp(b - a, c - a)) < EPS;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d", &t);
	puts("INTERSECTING LINES OUTPUT");
	for (int test = 1; test <= t; ++test) {
		double x1, y1, x2, y2, x3, y3, x4, y4;
		scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		point p;
		if (intersectSegments({x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}, p)) {
			printf("POINT %.2lf %.2lf\n", p.real(), p.imag());
		} else if (isCollinear({x1, y1}, {x2, y2}, {x3, y3})) {
			puts("LINE");
		} else {
			puts("NONE");
		}
	}
	puts("END OF OUTPUT");
	return 0;
}
