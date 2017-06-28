/*
	Author: Omar22
	Idea: dp
 	state: (index of old statue, index of the new statue)
 	*calculate the distance of each index
*/

#include <bits/stdc++.h>

using namespace std;
const int N = 2e3 + 1;
long double oldDistance, newDistance;
int n, m;
long double memo[N][N];
long double go(int i, int j) {
	if (j == m + n) {
		if (i == n)
			return 0;
		return 1e9;
	}
	long double &ret = memo[i][j];
	if (ret == ret)
		return ret;
	ret = go(i, j + 1);
	ret = min(ret, go(i + 1, j + 1) + fabs(i * oldDistance - j * newDistance));
	return ret;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	while (scanf("%d %d", &n, &m) != EOF) {
		oldDistance = 1e4 / n;
		newDistance = 1e4 / (n + m);
		memset(memo, -1, sizeof memo);
		printf("%.6Lf\n", go(0, 0));
	}
	return 0;
}

