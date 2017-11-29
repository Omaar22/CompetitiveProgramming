#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5, M = N * 4;

long long st[M], lazy[M];
int n;

void propagate(int l, int r, int i, int li, int ri) {
	if (lazy[i]) {
		st[i] += lazy[i] * (r - l + 1);
		if (l != r) {
			lazy[li] += lazy[i];
			lazy[ri] += lazy[i];
		}
		lazy[i] = 0;
	}
}

void update(int x, int y, int l = 1, int r = n, int i = 1) {
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	propagate(l, r, i, li, ri);
	if (x <= l && r <= y) {
		lazy[i] = 1;
		propagate(l, r, i, li, ri);
		return;
	}
	if (l > y || r < x)
		return;
	update(x, y, l, mid, li);
	update(x, y, mid + 1, r, ri);
	st[i] = st[li] + st[ri];
}

long long query(int x, int y, int l = 1, int r = n, int i = 1) {
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	propagate(l, r, i, li, ri);
	if (x <= l && r <= y) {
		return st[i];
	}
	if (l > y || r < x)
		return 0;
	return query(x, y, l, mid, li) + query(x, y, mid + 1, r, ri);
}
char s[22];
int x, y;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		memset(st, 0, sizeof st);
		memset(lazy, 0, sizeof lazy);
		printf("Scenario #%d:\n", test);
		int m;
		scanf("%d %d ", &n, &m);
		while (m--) {
			scanf("%s %d %d ", s, &x, &y);
			if (strcmp(s, "answer") == 0) {
				printf("%lld\n", query(x, y));
			} else {
				update(x, y);
				puts("OK");
			}
		}
	}
	return 0;
}
