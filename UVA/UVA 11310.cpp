/*
	Author: Omar22
	Idea: dp counting
 		  state: (row, is Empty Row, is Row not empty because I added a dot)
*/

#include <bits/stdc++.h>

using namespace std;
const int N = 40 + 1;
int n;
long long memo[N][2][2];
long long go(int i, bool dot, bool prevDot) {
	if (i >= n) {
		return i == n && !dot;
	}
	long long &ret = memo[i][dot][prevDot];
	if (ret != -1)
		return ret;
	ret = 0;
	if (!dot) {
		ret += go(i + 1, false, false); // for double dots
		ret += go(i, true, true); // add dot up
		ret += go(i, true, true); // add dot down
		ret += go(i + 1, true, false); // add L up
		ret += go(i + 1, true, false); // add L down
	} else if (prevDot) {
		ret += go(i + 2, false, false); // add L
	} else {
		ret += go(i + 1, false, true); // add dot
		ret += go(i + 2, false, false); // add L
	}
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		memset(memo, -1, sizeof memo);
		printf("%lld\n", go(0, 0, 0));
	}
	return 0;
}

