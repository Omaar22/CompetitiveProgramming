/*
	author: omar22
	idea: for each segment calculate minimum distance from segment to point and ternary search to find x, y values
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 1e3 + 1;
const double EPS = 1e-6;
typedef complex<double> point;
#define dp(a, b)                 ( (conj(a)*(b)).real() )    // a*b cos(T), if zero -> prep
#define length(a)               (hypot((a).imag(), (a).real()))


//distance from point p2 to segment p0-p1
double distToSegment(point p0, point p1, point p2) {
	double d1, d2;
	point v1 = p1 - p0, v2 = p2 - p0;
	if ((d1 = dp(v1, v2)) <= 0) return length(p2 - p0);
	if ((d2 = dp(v1, v1)) <= d1) return length(p2 - p1);
	double t = d1 / d2;
	return length(p2 - (p0 + v1 * t));
}
double f(double x0, double y0, double x1, double y1, double x, point c) {
//		(y0 - y1) * x + (x1 - x0) * y + (x0 * y1 - x1 * y0) = 0;
//		(y0 - y1) * x + (x0 * y1 - x1 * y0) = -(x1 - x0) * y;
	double y = ((y0 - y1) * x + (x0 * y1 - x1 * y0)) / -(x1 - x0);
	return (x - c.real()) * (x - c.real()) + (y - c.imag()) * (y - c.imag());
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	double x, y;
	while (scanf("%lf %lf", &x, &y) != EOF) {
		point c(x, y);
		int n;
		scanf("%d", &n);
		double mini = 1e18, resultX = -1e9, resultY = -1e9;
		double x1, y1;
		scanf("%lf %lf", &x1, &y1);
		for (int i = 0; i < n; ++i) {
			double x2, y2;
			scanf("%lf %lf", &x2, &y2);
			point a(x1, y1), b(x2, y2);
			double dis = distToSegment(a, b, c);
			if (dis < mini) {
				mini = dis;
				double l = x1, r = x2;
				for (int j = 0; j < 100; j++) {
					double l1 = (l * 2 + r) / 3;
					double l2 = (l + 2 * r) / 3;
					if (f(x1, y1, x2, y2, l1, c) < f(x1, y1, x2, y2, l2, c)) r = l2;
					else l = l1;
				}
				resultX = l;
				resultY = ((y1 - y2) * resultX + (x1 * y2 - x2 * y1)) / -(x2 - x1);
				if (x2 == x1) {
					if (y1 <= y && y <= y2 || y2 <= y && y <= y1)
						resultY = y;
					else if (y <= min(y1, y2))
						resultY = min(y1, y2);
					else
						resultY = max(y1, y2);
				}
			}
			x1 = x2;
			y1 = y2;
		}
		if (abs(resultX - 0) < EPS) // avoid print -0.0
			resultX = 0.0;
		if (abs(resultY - 0) < EPS)
			resultY = 0.0;
		assert(n != 0);
		printf("%.4lf\n%.4lf\n", resultX, resultY);
	}
	return 0;
	
}