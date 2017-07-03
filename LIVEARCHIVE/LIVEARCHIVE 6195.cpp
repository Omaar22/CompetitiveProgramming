#include <bits/stdc++.h>

using namespace std;
const int N = 1e4 + 1;
vector<int> adj[N];
int n, m;
int color[N];
bool isCycle(int node) {
	if (color[node])
		return color[node] == 1;
	color[node] = 1;
	bool ret = false;
	for (auto child: adj[node]) {
		ret |= isCycle(child);
	}
	color[node] = 2;
	return ret;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	while (true) {
		for (int i = 1; i <= n; ++i)
			adj[i].clear();
		memset(color, 0, sizeof color);
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)
			break;
		int inGoing[N] = {};
		for (int i = 0; i < m; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			assert(u != v);
			adj[u].push_back(v);
			++inGoing[v];
		}
		bool cycle = false;
		for (int i = 1; i <= n; ++i) {
			if (isCycle(i)) {
				cycle = true;
			}
		}
		if (cycle) {
			printf("0\n");
			continue;
		}
		int root = 0;
		for (int i = 1; i <= n; ++i) {
			if (!inGoing[i]) {
				if (root == 0) {
					root = i;
				} else {
					root = -1;
				}
			}
		}
		if (root <= 0) {
			printf("2\n");
			continue;
		}
		queue<int> q;
		q.push(root);
		bool unique = true;
		while (q.size()) {
			if (q.size() > 1)
				unique = false;
			auto node = q.front();
			q.pop();
			for (auto child: adj[node]) {
				--inGoing[child];
				if (!inGoing[child]) {
					q.push(child);
				}
			}
		}
		if (unique)
			printf("1\n");
		else
			printf("2\n");
	}
	
	return 0;
}
 
