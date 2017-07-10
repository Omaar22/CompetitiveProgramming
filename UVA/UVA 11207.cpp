/*
	author: omar22
	idea: brute force,
 		the maximum area for each rectangle is either to cut it into 4 * 1 squares or 2 * 2 squares
 */
#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	
	while (true) {
		int n;
		scanf("%d", &n);
		if (n == 0)
			break;
		double area = 0;
		int index = -1;
		for (int i = 1; i <= n; ++i) {
			int w, h;
			scanf("%d %d", &w, &h);
			double a = min(max(w, h) / 4.0, (double) min(w, h));
			a = max(a, min(w / 2.0, h / 2.0));
			if (a > area) {
				area = a;
				index = i;
			}
		}
		printf("%d\n", index);
	}
	
	
	return 0;
}
