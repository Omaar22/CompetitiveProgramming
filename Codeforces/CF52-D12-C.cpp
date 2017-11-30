#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 2, M = N * 4;

long long st[M], lazy[M];
int n, a[N];

void build(int l = 1, int r = n, int i = 1) {
	if (l == r) {
		st[i] = a[r];
		return;
	}
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	build(l, mid, li);
	build(mid + 1, r, ri);
	st[i] = min(st[li], st[ri]);
}

void propagate(int l, int r, int i, int li, int ri) {
	if (lazy[i] == 0)
		return;
	st[i] += lazy[i];
	if (l != r) {
		st[li] += lazy[i];
		st[ri] += lazy[i];
	}
	lazy[i] = 0;
}

void update(int x, int y, int v, int l = 1, int r = n, int i = 1) {
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	propagate(l, r, i, li, ri);
	if (x <= l && r <= y) {
		lazy[i] = v;
		propagate(l, r, i, li, ri);
		return;
	}
	if (x > r || y < l)
		return;
	update(x, y, v, l, mid, li);
	update(x, y, v, mid + 1, r, ri);
	st[i] = min(st[li], st[ri]);
}

long long query(int x, int y, int l = 1, int r = n, int i = 1) {
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	propagate(l, r, i, li, ri);
	if (x <= l && r <= y)
		return st[i];
	if (x > r || y < l)
		return 1e18;
	return min(query(x, y, l, mid, li), query(x, y, mid + 1, r, ri));
}
char line[N];
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	build();
	int q;
	scanf("%d ", &q);
	while (q--) {
		int x = 2e6, y = 2e6, v = 2e6;
		gets(line);
		string cur;
		for (int i = 0; line[i]; ++i) {
			if (line[i] == ' ') {
				if (x == 2e6) {
					x = stoi(cur);
				} else if (y == 2e6) {
					y = stoi(cur);
				}
				cur = "";
			} else {
				cur += line[i];
			}
		}
		if (y == 2e6)
			y = stoi(cur);
		else
			v = stoi(cur);
		++x;
		++y;
		if (v == 2e6) {
			if (x <= y)
				printf("%lld\n", query(x, y));
			else
				printf("%lld\n", min(query(x, n), query(1, y)));
		} else {
			if (x <= y) {
				update(x, y, v);
			} else {
				update(x, n, v);
				update(1, y, v);
			}
		}
	}
	return 0;
}
