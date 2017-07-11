/*
	author: omar22
 	idea: brute force
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 27;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int test = 0;
	while (++test) {
		int n;
		scanf("%d", &n);
		if (n == 0)
			break;
		char c[N];
		int x[N], y[N];
		for (int i = 0; i < n; ++i) {
			scanf(" %c %d %d", c + i, x + i, y + i);
		}
		set<string> result;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < n; ++k) {
					for (int w = 0; w < n; ++w) {
						if (i == j || i == k || i == w || j == k | j == w || k == w)
							continue;
						// j k
						// i w
						if (x[i] == x[j] && x[k] == x[w] && y[j] == y[k] && y[i] == y[w] && x[j] < x[k] &&
							y[i] < y[j]) {
							string tmp;
							tmp = c[j];
							tmp += c[k];
							tmp += c[w];
							tmp += c[i];
							result.insert(tmp);
						}
					}
				}
			}
		}
		printf("Point set %d:", test);
		if (result.empty()) {
			puts(" No rectangles");
		} else {
			int i = 0;
			for (auto a: result) {
				if (i++ % 10 == 0)
					printf("\n");
				printf(" %s", a.c_str());
			}
			printf("\n");
		}
	}
	
	return 0;
}
