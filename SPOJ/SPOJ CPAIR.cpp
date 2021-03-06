/*
 * sort queries decreasing on V
 * add index of number >= V to DSU
 * for each segment of contigous indices are component
 * for each component, for each i from 1 to sz, add values from sz to 1 respectivley (using segment tree)
 * answer query on segment tree from a to b
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 3, M = 1e3 + 2;

int parent[N], sz[N], rnk[N], n;

void init() {
	for (int i = 0; i <= n + 1; ++i) {
		parent[i] = i;
		sz[i] = 1;
		rnk[i] = 0;
	}
}

int root(int node) {
	while (node != parent[node]) {
		parent[node] = parent[parent[node]];
		node = parent[node];
	}
	return node;
}

bool join(int u, int v) {
	u = root(u);
	v = root(v);
	if (u == v)
		return false;
	if (rnk[u] < rnk[v])
		swap(u, v);
	rnk[u] += rnk[u] == rnk[v];
	sz[u] += sz[v];
	parent[v] = u;
	return true;
}
bool find(int u, int v) {
	return root(u) == root(v);
}
vector<int> occ[M];

struct Query {
	int a, b, v, i;
	bool operator<(const Query &e) const {
		return v > e.v;
	}
} queries[N];

long long st[N * 4], lazyV[N * 4], lazyC[N * 4];
long long f(long long x) {
	return x * (x + 1) / 2;
}
void propagate(int l, int r, int i, int li, int ri) {
	if (lazyC[i] || lazyV[i]) {
		int len = (r - l + 1);
		st[i] += lazyV[i] * len + lazyC[i] * len - lazyC[i] * (f(r) - f(l - 1));
		if (l != r) {
			lazyV[li] += lazyV[i];
			lazyV[ri] += lazyV[i];
			lazyC[li] += lazyC[i];
			lazyC[ri] += lazyC[i];
		}
		lazyV[i] = lazyC[i] = 0;
	}
}

void update(int x, int y, int v, int l = 1, int r = n, int i = 1) {
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	propagate(l, r, i, li, ri);
	if (x <= l && r <= y) {
		lazyV[i] += v;
		if (v < 0)
			lazyC[i] -= 1;
		else
			lazyC[i] += 1;
		
		propagate(l, r, i, li, ri);
		return;
	}
	if (l > y || r < x)
		return;
	update(x, y, v, l, mid, li);
	update(x, y, v, mid + 1, r, ri);
	st[i] = st[li] + st[ri];
}

long long query(int x, int y, int l = 1, int r = n, int i = 1) {
	int mid = (l + r) / 2, li = mid * 2, ri = li + 1;
	propagate(l, r, i, li, ri);
	if (x <= l && r <= y)
		return st[i];
	if (l > y || r < x)
		return 0;
	return query(x, y, l, mid, li) + query(x, y, mid + 1, r, ri);
}
bool in[N];
void add(int prev, int v) {
	for (int i = prev - 1; i >= v; --i) {
		for (auto idx: occ[i]) {
			in[idx] = true;
			int len = 1;
			update(1, len, len);
			if (in[idx + 1]) {
				// negative
				update(1, len, -len);
				
				int u = root(idx + 1);
				len = sz[u];
				// negative
				update(1, len, -len);
				
				join(idx, idx + 1);
				u = root(idx);
				len = sz[u];
				update(1, len, len);
			}
			if (in[idx - 1]) {
				// negative
				update(1, len, -len);
				
				int u = root(idx - 1);
				len = sz[u];
				// negative
				update(1, len, -len);
				
				join(idx, idx - 1);
				u = root(idx);
				len = sz[u];
				update(1, len, len);
			}
		}
	}
}

long long res[N];
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int q, prev = -1;
	scanf("%d %d", &n, &q);
	init();
	for (int i = 1; i <= n; ++i) {
		int a;
		scanf("%d", &a);
		occ[a].push_back(i);
		prev = max(prev, a + 1);
	}
	for (int i = 0; i < q; ++i) {
		scanf("%d %d %d", &queries[i].v, &queries[i].a, &queries[i].b), queries[i].i = i;
		queries[i].b = min(queries[i].b, n);
	}
	sort(queries, queries + q);
	for (int i = 0; i < q; ++i) {
		add(prev, queries[i].v);
		res[queries[i].i] = query(queries[i].a, queries[i].b);
		prev = queries[i].v;
	}
	for (int i = 0; i < q; ++i)
		printf("%lld\n", res[i]);
	return 0;
}
