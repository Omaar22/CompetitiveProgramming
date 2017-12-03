/*
 * author: omar22
 * idea:
 *		segment tree, shift the array by updating every v[i] with v[i + 1]
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, M = N * 4;
int a[N], n, st[M];
char str[31];

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

void update(int x, int v, int l = 1, int r = n, int i = 1) {
	if (l == r) {
		st[i] = v;
		return;
	}
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	if (x <= mid)
		update(x, v, l, mid, li);
	else
		update(x, v, mid + 1, r, ri);
	st[i] = min(st[li], st[ri]);
}
int query(int x, int y, int l = 1, int r = n, int i = 1) {
	if (x <= l && r <= y)
		return st[i];
	if (x > r || y < l)
		return 1e9;
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	return min(query(x, y, l, mid, li), query(x, y, mid + 1, r, ri));
}
vector<int> parse() {
	int i = 0;
	while (str[i++] != '(');
	int cur = 0;
	vector<int> ret;
	for (; str[i]; ++i) {
		if (isdigit(str[i])) {
			cur = cur * 10 + str[i] - '0';
		} else {
			ret.push_back(cur);
			cur = 0;
		}
	}
	sort(ret.begin(), ret.end());
	return ret;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	build();
	while (q--) {
		scanf(" %s", str);
		if (str[0] == 'q') {
			auto v = parse();
			printf("%d\n", query(v[0], v[1]));
		} else {
			auto v = parse();
			int zero = query(v[0], v[0]);
			for (int i = 0; i < v.size(); ++i) {
				int val;
				if (i + 1 != v.size())
					val = query(v[i + 1], v[i + 1]);
				else
					val = zero;
				update(v[i], val);
			}
		}
	}
	return 0;
}
