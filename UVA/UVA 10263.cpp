/*
	author: omar22
	idea: for each segment calculate minimum distance from segment to point using ternary search
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 1e3 + 1;
const double EPS = 1e-6;
typedef complex<double> point;
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
			double l = x1, r = x2;
			for (int j = 0; j < 100; j++) {
				double l1 = (l * 2 + r) / 3;
				double l2 = (l + 2 * r) / 3;
				if (f(x1, y1, x2, y2, l1, c) < f(x1, y1, x2, y2, l2, c)) r = l2;
				else l = l1;
			}
			double dis = f(x1, y1, x2, y2, l, c);
			if (dis > mini) {
				continue;
			}
			resultX = l;
			resultY = ((y1 - y2) * resultX + (x1 * y2 - x2 * y1)) / -(x2 - x1);
			mini = f(x1, y1, x2, y2, l, c);
			if (x2 == x1) {
				if (y1 <= y && y <= y2 || y2 <= y && y <= y1)
					resultY = y;
				else if (y <= min(y1, y2))
					resultY = min(y1, y2);
				else
					resultY = max(y1, y2);
			}
			x1 = x2;
			y1 = y2;
		}
		printf("%.4lf\n%.4lf\n", resultX, resultY);
	}
	return 0;
	
}
