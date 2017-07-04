/*
	author: omar22
	idea: the common area is a rectangle with side = (maxX1, maxY1) (minX2, minY2)
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 33, M = 1e4 + 1;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		int n, maxX1 = -M, minX2 = M, maxY1 = -M, minY2 = M;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			maxX1 = max(maxX1, x1);
			minX2 = min(minX2, x2);
			maxY1 = max(maxY1, y1);
			minY2 = min(minY2, y2);
		}
		int result = (minX2 - maxX1) * (minY2 - maxY1);
		if (minX2 < maxX1 || minY2 < maxY1) {
			result = 0;
		}
		printf("Case %d: %d\n", test, result);
	}
	
	return 0;
	
}