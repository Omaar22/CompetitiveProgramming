/*
	author: omar22
	idea: since there are infinite solutions (different square sides),
 		just calculate the perpendicular vectors (assume side is almost = 0)
 */
#include <bits/stdc++.h>

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	double x1, y1, x2, y2;
	while (scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2) != EOF) {
		double dx = (x2 - x1) / 2;
		double dy = (y2 - y1) / 2;
		double x = (x1 + x2) / 2;
		double y = (y1 + y2) / 2;
		printf("%.10lf %.10lf %.10lf %.10lf\n", x + dy, y - dx, x - dy, y + dx);
	}
	return 0;
}
