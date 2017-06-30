/*
	Author: Omar22
	Idea:
*/

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
vector<int> topologicalLeft, topologicalRight;
bool visLeft[N], visRight[N];
void goLeft(int node) {
	if (visLeft[node]++)
		return;
	for (auto child: adj[node]) {
		goLeft(child);
	}
	topologicalLeft.push_back(node);
}
void goRight(int node) {
	if (visRight[node]++)
		return;
	for (int i = adj[node].size() - 1; i >= 0; --i) {
		goRight(adj[node][i]);
	}
	topologicalRight.push_back(node);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d", &t);
	while (t--) {
		topologicalRight.clear();
		topologicalLeft.clear();
		for (int i = 1; i <= n; ++i)
			adj[i].clear();
		memset(visLeft, 0, sizeof visLeft);
		memset(visRight, 0, sizeof visRight);
		memset(color, 0, sizeof color);
		scanf("%d %d", &n, &m);
		vector<bool> isRoot(N, 1);
		for (int i = 0; i < m; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			adj[v].push_back(u);
			isRoot[u] = false;
		}
		bool recheck = false;
		for (int i = 1; i <= n; ++i) {
			if (isCycle(i)) {
				recheck = true;
			}
		}
		if (recheck) {
			printf("recheck hints\n");
			continue;
		}
		int root = 0;
		for (int i = 1; i <= n; ++i) {
			if (isRoot[i]) {
				if (root == 0)
					root = i;
				else
					root = -1;
			}
		}
		if (root <= 0) {
			printf("missing hints\n");
			continue;
		}
		goLeft(root);
		goRight(root);
		if (topologicalRight == topologicalLeft) {
			for (auto node: topologicalRight)
				printf("%d ", node);
			printf("\n");
		} else {
			printf("missing hints\n");
		}
	}
	
	return 0;
}

