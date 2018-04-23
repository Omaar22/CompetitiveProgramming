#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, M = 1e3 + 3;

struct Pair {
	int f, s, i;
	bool operator<(const Pair &other) const {
		if (f != other.f)
			return f < other.f;
		return s < other.s;
	}
} p[N];

bool cmp(const Pair &a, const Pair &b) {
	return a.i < b.i;
}

int st[4 * N], visID[N * 4], vis, n;
int dp[N], parent[N];
map<int, int> id;

void update(int x, int val, int l = 0, int r = id.size() - 1, int i = 1) {
	int li = i << 1, ri = li + 1;
	if (x < l || r < x)
		return;
	if (l == r) {
		if (visID[i] != vis || dp[val] > dp[st[i]]) {
			st[i] = val;
			visID[i] = vis;
		}
		return;
	}
	int mid = (l + r) >> 1;
	update(x, val, l, mid, li);
	update(x, val, mid + 1, r, ri);
	
	if (visID[li] == vis && visID[ri] == vis) {
		if (dp[st[li]] >= dp[st[ri]])
			st[i] = st[li];
		else
			st[i] = st[ri];
	} else if (visID[li] == vis) {
		st[i] = st[li];
	} else {
		st[i] = st[ri];
	}
	visID[i] = vis;
}

int query(int x, int y, int l = 0, int r = id.size() - 1, int i = 1) {
	int li = i << 1, ri = li + 1;
	if (r < x || l > y)
		return n;
	if (x <= l && r <= y) {
		if (visID[i] == vis)
			return st[i];
		return n;
	}
	int mid = (l + r) >> 1;
	int ql = query(x, y, l, mid, li);
	int qr = query(x, y, mid + 1, r, ri);
	if (dp[ql] >= dp[qr])
		return ql;
	else
		return qr;
}
void go(int s, int e) {
	if (s == e)
		return;
	int m = (s + e) / 2;
	go(s, m);
	sort(p + s, p + m + 1);
	sort(p + m + 1, p + e + 1);
	
	++vis;
	
	int j = s;
	for (int i = m + 1; i <= e; ++i) {
		while (j <= m && p[i].f > p[j].f) {
			update(id[p[j].s], p[j].i);
			++j;
		}
		int index = query(0, id[p[i].s] - 1);
		if (dp[p[i].i] < dp[index] + 1) {
			dp[p[i].i] = dp[index] + 1;
			parent[p[i].i] = index;
		}
	}
	sort(p + s, p + e + 1, cmp);
	go(m + 1, e);
}
int tmp[N];
int arr[11][M];
int lis[N], A[N], idx[N], len;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
//	freopen("output.out", "w", stdout);
#endif
	int m;
	scanf("%d %d", &m, &n);
	for (int i = 0; i < n; ++i) {
		dp[i] = 1;
		parent[i] = -1;
	}
	if (m == 1) {
		for (int i = 0; i < n; ++i)
			scanf("%d", A + i);
		for (int i = 0; i < n; ++i) {
			int index = lower_bound(lis, lis + len, A[i]) - lis;
			lis[index] = A[i];
			idx[index] = i;
			if (index)
				parent[i] = idx[index - 1];
			else
				parent[i] = -1;
			len = max(len, index + 1);
		}
		
		vector<int> ans;
		int cur = idx[len - 1];
		while (~cur) {
			ans.push_back(cur);
			cur = parent[cur];
		}
		for (int i = ans.size() - 1; i >= 0; --i)
			printf("%d%c", ans[i] + 1, " \n"[i == 0]);
		return 0;
	} else if (m == 2) {
		for (int i = 0; i < n; ++i)
			scanf("%d", &p[i].f);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &p[i].s);
			p[i].i = i;
			tmp[i] = p[i].s;
		}
		sort(tmp, tmp + n);
		int index = 0;
		for (int i = 0; i < n; ++i)
			if (id.insert({tmp[i], index}).second)
				++index;
		go(0, n - 1);
	} else {
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				scanf("%d", arr[i] + j);
		
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < i; ++j) {
				bool valid = true;
				for (int k = 0; k < m; ++k) {
					if (arr[k][i] <= arr[k][j]) {
						valid = false;
						break;
					}
				}
				if (valid && dp[i] < dp[j] + 1) {
					dp[i] = dp[j] + 1;
					parent[i] = j;
				}
			}
		}
	}
	int maxi = 0;
	int index = -1;
	for (int i = 0; i < n; ++i) {
		if (dp[i] > maxi) {
			maxi = dp[i];
			index = i;
		}
	}
	vector<int> res;
	while (~index) {
		res.push_back(index + 1);
		index = parent[index];
	}
	for (int i = res.size() - 1; i >= 0; --i)
		printf("%d%c", res[i], " \n"[i == 0]);
	return 0;
}

