/*
	Author: Omar22
	Idea: dp counting
 		  state: (row, number of secured drawers, is the above drawers locked)
*/

#include <bits/stdc++.h>

using namespace std;
const int N = 66 + 1;
int n, s;
long long memo[N][N][2];
long long go(int i, int save, bool prevLocked) {
	if (i == 0) {
		return save == s;
	}
	long long &ret = memo[i][save][prevLocked];
	if (ret != -1)
		return ret;
	ret = go(i - 1, save, false);
	if (prevLocked)
		ret += go(i - 1, save + 1, true);
	else
		ret += go(i - 1, save, true);
	return ret;
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	while (true) {
		scanf("%d %d", &n, &s);
		if (n <= 0)
			break;
		memset(memo, -1, sizeof memo);
		printf("%lld\n", go(n, 0, true));
	}
	return 0;
}

