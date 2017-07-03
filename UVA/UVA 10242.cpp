/*
	author: omar22
	idea: add the two vectors to the common point
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 1e4 + 1;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	double x[4], y[4];
	while (true) {
		for (int i = 0; i < 4; ++i) {
			if (scanf("%lf %lf", x + i, y + i) == EOF)
				return 0;
		}
		if (x[0] == x[2] && y[0] == y[2]) {
			double dx = x[1] - x[0] + x[3] - x[2];
			double dy = y[1] - y[0] + y[3] - y[2];
			printf("%.9lf %.9lf\n", x[0] + dx, y[0] + dy);
		} else if (x[0] == x[3] && y[0] == y[3]) {
			double dx = x[1] - x[0] + x[2] - x[3];
			double dy = y[1] - y[0] + y[2] - y[3];
			printf("%.9lf %.9lf\n", x[0] + dx, y[0] + dy);
		} else if (x[1] == x[2] && y[1] == y[2]) {
			double dx = x[0] - x[1] + x[3] - x[2];
			double dy = y[0] - y[1] + y[3] - y[2];
			printf("%.9lf %.9lf\n", x[1] + dx, y[1] + dy);
		} else if (x[1] == x[3] && y[1] == y[3]) {
			double dx = x[0] - x[1] + x[2] - x[3];
			double dy = y[0] - y[1] + y[2] - y[3];
			printf("%.9lf %.9lf\n", x[1] + dx, y[1] + dy);
		} else {
			assert(false);
		}
	}
	return 0;
	
}