#include <bits/stdc++.h>

using namespace std;

const int N = 3e4 + 2, M = N * 4;

int stClosed[M], stOpen[M], n;
char s[N];

void build(int l = 1, int r = n, int i = 1) {
	if (l == r) {
		stClosed[i] = s[r] == ')';
		stOpen[i] = s[r] == '(';
		return;
	}
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	build(l, mid, li);
	build(mid + 1, r, ri);
	
	stOpen[i] = max(0, stOpen[li] - stClosed[ri]) + stOpen[ri];
	stClosed[i] = max(0, stClosed[ri] - stOpen[li]) + stClosed[li];
}

void update(int x, int l = 1, int r = n, int i = 1) {
	if (l == r) {
		if (s[r] == ')')
			s[r] = '(';
		else
			s[r] = ')';
		stClosed[i] = s[r] == ')';
		stOpen[i] = s[r] == '(';
		return;
	}
	
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	if (x <= mid) {
		update(x, l, mid, li);
	} else {
		update(x, mid + 1, r, ri);
	}
	stOpen[i] = max(0, stOpen[li] - stClosed[ri]) + stOpen[ri];
	stClosed[i] = max(0, stClosed[ri] - stOpen[li]) + stClosed[li];
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	for (int test = 1; test <= 10; ++test){
		printf("Test %d:\n", test);
		scanf("%d %s", &n, s + 1);
		build();
		int q;
		scanf("%d", &q);
		while (q--) {
			int k;
			scanf("%d", &k);
			if (k) {
				update(k);
			} else {
				if (stOpen[1] || stClosed[1])
					puts("NO");
				else
					puts("YES");
			}
		}
	}
	return 0;
}
