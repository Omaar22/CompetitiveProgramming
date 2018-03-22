#include <bits/stdc++.h>

using namespace std;
const int N = 5e3 + 3;
int n, p[N];

void permute() {
	for (int i = 0; i < n * 5; ++i)
		p[i] = i;
	int a[N][5];
	for (int i = 0; i < n; ++i)
		a[i][0] = p[i * 2], a[i][1] = p[i * 2 + 1], a[i][2] = p[n * 2 + i * 2], a[i][3] = p[n * 2 + i * 2 + 1], a[i][4] = p[n * 4 + i];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 5; ++j)
			p[i * 5 + j] = a[i][j];
//	for (int i = 0; i < n * 5; ++i)
//		cout << p[i] + 1 << " ";
//	cout << endl;
}
vector<vector<int>> comp;
pair<int, int> inComp[N];
bool vis[N];
void build() {
	for (int i = 0; i < n * 5; ++i) {
		if (vis[i])
			continue;
		int node = i;
		vector<int> cur;
		do {
			vis[node] = true;
			inComp[node] = {comp.size(), cur.size()};
			cur.push_back(node);
			node = p[node];
		} while (!vis[node]);
		comp.push_back(cur);
	}
}
long long EGCD(long long r0, long long r1, long long &x0, long long &y0) {
	long long y1 = x0 = 1, x1 = y0 = 0;
	while (r1) {
		long long r = (r0 / r1), t;
		t = r0 - r * r1, r0 = r1, r1 = t;
		t = x0 - r * x1, x0 = x1, x1 = t;
		t = y0 - r * y1, y0 = y1, y1 = t;
	}
	return r0;
}
bool solveLDE(long long a, long long b, long long c, long long &x, long long &y, long long &g) {
	g = EGCD(a, b, x, y);
	long long m = c / g;
	x *= m;
	y *= m;
	return !(c % g);
}

bool CRT(const vector<long long> &r, const vector<long long> &m, long long &R, long long &M) {
	R = r[0], M = m[0];
	for (int i = 1; i < (int) r.size(); i++) {
		long long m1 = M, m2 = m[i], r1 = R, r2 = r[i];
		long long p1, p2, g;
		if (!solveLDE(m1, m2, r2 - r1, p1, p2, g)) return false;
		long long mod = m2 / g;
		p1 = ((p1 % mod) + mod) % mod;
		M = m1 / g * m2;
		R = (p1 * m1) % M + r1;
		R = ((R % M) + M) % M;
	}
	return 1;
}
int rev[N];
long long check(int player, int *target, vector<long long> &r, vector<long long> &m) {
	for (int j = 0; j < 5; ++j) {
		int init = rev[target[j]];
		int curC = inComp[init].first;
		int curI = inComp[init].second;
		int targetC = inComp[j + player * 5].first;
		int targetI = inComp[j + player * 5].second;
		long long steps = curI - targetI;
		if (steps < 0)
			steps += comp[curC].size();
		m.push_back(comp[curC].size());
		r.push_back(steps);
		if (targetC != curC)
			return -1;
	}
	long long R, M;
	if (!CRT(r, m, R, M))
		return -2;
	if (R <= 0)
		R += M;
	return R;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "rt", stdin);
	freopen("output.out", "wt", stdout);
#endif
	while (~scanf("%d", &n) && n) {
		memset(vis, 0, sizeof vis);
		permute();
		build();
		for (int i = 0; i < n * 5; ++i) {
			scanf("%d", p + i);
			--p[i];
			rev[p[i]] = i;
		}
		vector<long long> r, m;
		int winner = -1;
		long long game = 4e18;
		for (int i = 0; i < n; ++i) {
			int target[] = {0, 1, 2, 3, 4};
			do {
				r.clear();
				m.clear();
				long long x = check(i, target, r, m);
				if (x >= 0 && x < game) {
					game = x;
					winner = i + 1;
				}
			} while (next_permutation(target, target + 5));
		}
		if (~winner) {
			printf("Player %d wins game number %lld.\n", winner, game);
		} else {
			puts("Neverending game.");
		}
	}
	return 0;
}
