#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5, M = N * 4;

int st[M], lazy[M], n;

void propagate(int l, int r, int i, int li, int ri) {
	if (lazy[i] == 0)
		return;
	if (lazy[i] % 2)
		st[i] = (r - l + 1) - st[i];
	if (l != r) {
		lazy[li] += lazy[i];
		lazy[ri] += lazy[i];
	}
	lazy[i] = 0;
}

void update(int x, int y, int l = 1, int r = n, int i = 1) {
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	propagate(l, r, i, li, ri);
	if (x <= l && r <= y) {
		lazy[i] = 1;
		propagate(l, r, i, li, ri);
		return;
	}
	if (x > r || l > y)
		return;
	update(x, y, l, mid, li);
	update(x, y, mid + 1, r, ri);
	st[i] = st[li] + st[ri];
}

int query(int x, int y, int l = 1, int r = n, int i = 1) {
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	propagate(l, r, i, li, ri);
	if (x <= l && r <= y) {
		return st[i];
	}
	if (x > r || l > y)
		return 0;
	return query(x, y, l, mid, li) + query(x, y, mid + 1, r, ri);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int m;
	scanf("%d %d", &n, &m);
	while (m--) {
		int type, x, y;
		scanf("%d %d %d", &type, &x, &y);
		if (type == 0) {
			update(x, y);
		} else {
			printf("%d\n", query(x, y));
		}
	}
	return 0;
}
