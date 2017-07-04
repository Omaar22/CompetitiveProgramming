/*
	author: omar22
	idea: for each segment calculate minimum distance from segment to point using ternary search
 */
#include <bits/stdc++.h>

using namespace std;

double f(double x1, double y1, double x2, double y2, double x, double targetX, double targetY) {
//		(y1 - y2) * x + (x2 - x1) * y + (x1 * y2 - x2 * y1) = 0;
	double y = ((y1 - y2) * x + (x1 * y2 - x2 * y1)) / -(x2 - x1);
	return hypot(x - targetX, y - targetY);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	double x, y;
	while (scanf("%lf %lf", &x, &y) != EOF) {
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
				if (f(x1, y1, x2, y2, l1, x, y) < f(x1, y1, x2, y2, l2, x, y)) r = l2;
				else l = l1;
			}
			double dis = f(x1, y1, x2, y2, l, x, y);
			if (dis > mini) {
				continue;
			}
			mini = dis;
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
			x1 = x2;
			y1 = y2;
		}
		printf("%.4lf\n%.4lf\n", resultX, resultY);
	}
	return 0;
	
}
