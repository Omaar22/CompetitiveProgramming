/*
 	author: omar22
 	idea:
 		assume dp n^3:
 		dp (index, allowed):
 			loop c = 1; c <= allowed; c++:
 				ret = maximum(ret, dp(index + c, c * 2) + sumRange[index to index + c - 1])
		I use extra bool parameter to specify the 'maximum' operator but it is not necessary
		
		The trick is to substitute the loop with self calls:
			ret = dp(i, allowed - 1)
 		and when picking, pick the whole allowed:
 			ret = dp(i + allowed, allowed * 2) + sumRange[index to index + allowed - 1]
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 3;
int n, a[N], cum[N];
pair<int, int> mem[N][N][2];
pair<int, int> go(int i, int k, bool player) {
	if (k == 0 || i > n + 1)
		return {-1e9, -1e9};
	if (i == n + 1)
		return {0, 0};
	pair<int, int> &ret = mem[i][k][player];
	if (~ret.first)
		return ret;
	ret = go(i, k - 1, player);
	auto tmp = go(i + k, min(n, k * 2), !player);
	if (player)
		tmp.first += cum[i + k - 1] - cum[i - 1];
	else
		tmp.second += cum[i + k - 1] - cum[i - 1];
	if (player && ret.first < tmp.first)
		ret = tmp;
	else if (!player && ret.second < tmp.second)
		ret = tmp;
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = 1; i <= n; ++i)
		cum[i] = cum[i - 1] + a[i];
	memset(mem, -1, sizeof mem);
	printf("%d\n", go(1, 2, true).first);
	return 0;
}
