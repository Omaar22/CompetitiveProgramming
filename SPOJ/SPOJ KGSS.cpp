/*
	author: omar22
	idea:
 		- Segment tree, each node contains the max 2 elements 
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2, M = N * 4;

int a[N], n;
pair<int, int> st[M];
void build(int l = 1, int r = n, int i = 1) {
	if (l == r) {
		st[i] = {a[r], -1e9};
		return;
	}
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	build(l, mid, li);
	build(mid + 1, r, ri);
	int a[4] = {st[li].first, st[li].second, st[ri].first, st[ri].second};
	sort(a, a + 4);
	st[i] = {a[2], a[3]};
}

void update(int x, int v, int l = 1, int r = n, int i = 1) {
	if (l == r) {
		st[i] = {v, -1e9};
		return;
	}
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	if (x <= mid)
		update(x, v, l, mid, li);
	else
		update(x, v, mid + 1, r, ri);
	int a[4] = {st[li].first, st[li].second, st[ri].first, st[ri].second};
	sort(a, a + 4);
	st[i] = {a[2], a[3]};
}

pair<int, int> query(int x, int y, int l = 1, int r = n, int i = 1) {
	if (x <= l && r <= y)
		return st[i];
	if (x > r || y < l)
		return {-1e9, -1e9};
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	auto left = query(x, y, l, mid, li);
	auto right = query(x, y, mid + 1, r, ri);
	int a[4] = {left.first, left.second, right.first, right.second};
	sort(a, a + 4);
	return {a[2], a[3]};
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	build();
	int q;
	scanf("%d", &q);
	while (q--) {
		char type;
		int x, y;
		scanf(" %c %d %d", &type, &x, &y);
		if (type == 'U') {
			update(x, y);
		} else {
			auto a = query(x, y);
			printf("%d\n", a.first + a.second);
		}
	}
	return 0;
}
