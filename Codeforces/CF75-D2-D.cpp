/*
 * author: omar22
 * idea:
 * 		from each block you need to pre-calculate three things:
 * 			- maximum subsequence
 * 			- maximum prefix
 * 			- maximum suffix
 * 		now the result will be some continuous blocks, in each block you can either take the whole block or just a prefix or just a suffix
 * 		or the result will be just subsequence of only one block
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 5000 + 5, M = 55, O = 250000 + 5;
int n, m, l[M], a[M][N], order[O], cum[M][N], prefix[M], suffix[M], sub[M];
long long memo[O][2];
long long go(int i, bool started) {
	if (i == m + 1) {
		if (started)
			return 0;
		return -1e12;
	}
	long long &ret = memo[i][started];
	if (~ret)
		return ret;
	ret = go(i + 1, true) + cum[order[i]][l[order[i]]];
	
	if (started) {
		ret = max(ret, 1ll * prefix[order[i]]);
	} else {
		ret = max(ret, 1ll*sub[order[i]]);
		ret = max(ret, go(i + 1, false));
		ret = max(ret, 1ll * suffix[order[i]] + go(i + 1, true));
	}
	return ret;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", l + i);
		for (int j = 1; j <= l[i]; ++j) {
			scanf("%d", a[i] + j);
			cum[i][j] += cum[i][j - 1] + a[i][j];
			prefix[i] = max(prefix[i], cum[i][j]);
		}
		for (int j = l[i]; j >= 1; --j) {
			suffix[i] = max(suffix[i], cum[i][l[i]] - cum[i][j - 1]);
			if (j == l[i])
				suffix[i] = a[i][j];
		}
		sub[i] = cum[i][1];
		for (int j = 1; j <= l[i]; ++j) {
			for (int k = j; k <= l[i]; ++k) {
				sub[i] = max(sub[i], cum[i][k] - cum[i][j - 1]);
			}
		}
	}
	for (int i = 1; i <= m; ++i)
		scanf("%d", order + i);
	memset(memo, -1, sizeof memo);
	printf("%lld\n", go(1, 0));
	return 0;
}
