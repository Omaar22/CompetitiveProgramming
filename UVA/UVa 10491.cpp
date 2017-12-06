/*
 * author: omar22
 * idea:
 * 		sum probabilities
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 4e3 + 5;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int n, m, x;
	while (~scanf("%d %d %d", &n, &m, &x)) {
		long double result = 0;
		for (int i = 0; i < n; ++i) {
			result += (1.0 / (n + m)) * (1.0 * m / (n + m - x - 1));
		}
		for (int i = 0; i < m; ++i) {
			result += (1.0 / (n + m)) * (1.0 * (m - 1) / (n + m - x - 1));
		}
		
		printf("%.5Lf\n", result);
	}
	return 0;
}
