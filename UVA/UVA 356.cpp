/*
	author: omar22
	idea: brute force for each square
 			check if the 4 corners are inside the circle
 			or at least one corner is inside the circle
 */
#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);
const int d[4][2] = {{0, 0},
					 {0, 1},
					 {1, 0},
					 {1, 1}};
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int n;
	bool input = false;
	while (scanf("%d", &n) != EOF) {
		double r = (2 * n - 1) / 2.0;
		int total = 0, completely = 0;
		for (int i = 0; i < n + n; ++i) {
			for (int j = 0; j < n + n; ++j) {
				int in = 0;
				for (int k = 0; k < 4; ++k) {
					int x = i + d[k][0];
					int y = j + d[k][1];
					if (hypot(x, y) < r + EPS) {
						++in;
					}
				}
				if (in == 4) {
					++completely;
					++total;
				} else if (in) {
					++total;
				}
			}
		}
		if (input++)
			puts("");
		printf("In the case n = %d, %d cells contain segments of the circle.\n"
		"There are %d cells completely contained in the circle.\n", n, (total * 4 - completely * 4), completely * 4);
	}
	
	return 0;
}
