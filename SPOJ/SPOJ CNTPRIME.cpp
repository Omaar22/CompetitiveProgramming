#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5, M = N * 4, Z = 1e6 + 5;

int st[M], lazy[M], a[N], n;
bool isPrime[Z];

void build(int l = 1, int r = n, int i = 1) {
	if (l == r) {
		st[i] = isPrime[a[r]];
		return;
	}
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	build(l, mid, li);
	build(mid + 1, r, ri);
	st[i] = st[li] + st[ri];
}

void propagate(int l, int r, int i, int li, int ri) {
	if (lazy[i] == -1)
		return;
	st[i] = lazy[i] * (r - l + 1);
	if (l != r) {
		lazy[li] = lazy[i];
		lazy[ri] = lazy[i];
	}
	lazy[i] = -1;
}

void update(int x, int y, int val, int l = 1, int r = n, int i = 1) {
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	propagate(l, r, i, li, ri);
	if (x <= l && r <= y) {
		lazy[i] = isPrime[val];
		propagate(l, r, i, li, ri);
		return;
	}
	if (x > r || y < l)
		return;
	update(x, y, val, l, mid, li);
	update(x, y, val, mid + 1, r, ri);
	st[i] = st[li] + st[ri];
}

int query(int x, int y, int l = 1, int r = n, int i = 1) {
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	propagate(l, r, i, li, ri);
	if (x <= l && r <= y)
		return st[i];
	if (x > r || y < l)
		return 0;
	return query(x, y, l, mid, li) + query(x, y, mid + 1, r, ri);
}

void sieve() {
	memset(isPrime, 1, sizeof isPrime);
	isPrime[0] = isPrime[1] = 0;
	for (int i = 2; i < Z; ++i) {
		if (!isPrime[i])
			continue;
		for (int j = i + i; j < Z; j += i) {
			isPrime[j] = false;
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	sieve();
	int t;
	scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		memset(lazy, -1, sizeof lazy);
		memset(st, 0, sizeof st);
		printf("Case %d:\n", test);
		int q;
		scanf("%d %d", &n, &q);
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		build();
		while (q--) {
			int type, x, y;
			scanf("%d %d %d", &type, &x, &y);
			if (type == 0) {
				int v;
				scanf("%d", &v);
				update(x, y, v);
			} else {
				printf("%d\n", query(x, y));
			}
		}
	}
	return 0;
}
