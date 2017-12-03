/*
 * author: omar22
 * idea:
 *		segment tree lazy propagation, lazy of 4 types:
 *			- -1 	no update
 *			-  0 	node cover zeros
 *			-  1 	node cover ones
 *			-  2 	invert node
 *		easily overwrite lazy of children of type 0 and 1 easily, but handle type 2
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 1024000 + 5, M = N * 4;
int n, st[M], lazy[M]; // lazy = 0 set 0, lazy = 1 set 1 lazy = 2 invert
string a;
char str[51];

void build(int l = 1, int r = n, int i = 1) {
	lazy[i] = -1; // clear lazy
	if (l == r) {
		st[i] = a[r] - '0';
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
	if (lazy[i] == 0)
		st[i] = 0;
	else if (lazy[i] == 1)
		st[i] = r - l + 1;
	else
		st[i] = (r - l + 1) - st[i];
	if (l != r) {
		if (lazy[i] != 2) {
			lazy[li] = lazy[i];
			lazy[ri] = lazy[i];
		} else {
			if (lazy[li] != -1)
				lazy[li] = 1 - lazy[li];
			else
				lazy[li] = 2;
			if (lazy[ri] != -1)
				lazy[ri] = 1 - lazy[ri];
			else
				lazy[ri] = 2;
		}
	}
	lazy[i] = -1;
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

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		printf("Case %d:\n", test);
		a = ".";
		int m;
		scanf("%d", &m);
		while (m--) {
			int f;
			scanf("%d %s", &f, str);
			while (f--) a += str;
		}
		n = a.size() - 1;
		build();
		int q, id = 0;
		scanf("%d", &q);
		while (q--) {
			char type;
			int x, y;
			scanf(" %c %d %d", &type, &x, &y);
			++x;
			++y;
			if (type == 'F') {
				update(x, y, 1);
			} else if (type == 'E') {
				update(x, y, 0);
			} else if (type == 'I') {
				update(x, y, 2);
			} else {
				printf("Q%d: %d\n", ++id, query(x, y));
			}
		}
	}
	return 0;
}
