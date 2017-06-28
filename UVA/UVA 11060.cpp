/*
	Author: Omar22
	Idea: do N topological sort from each node without visit O(N^2)
 		  then merge the outputs by the order of input
*/

#include <bits/stdc++.h>

using namespace std;
const int N = 1e2 + 1;
vector<vector<int>> topological;
vector<int> adj[N];
int vis[N], test;
char s[N][N];
void dfs(int node) {
	for (auto child: adj[node]) {
		dfs(child);
	}
	topological.back().push_back(node);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int n;
	while (scanf("%d", &n) != EOF) {
		printf("Case #%d: Dilbert should drink beverages in this order: ", ++test);
		map<string, int> ID;
		for (int i = 1; i <= n; ++i) {
			scanf(" %s", s[i]);
			ID[string(s[i])] = i;
		}
		int m;
		scanf("%d", &m);
		while (m--) {
			char a[N], b[N];
			scanf("%s %s", a, b);
			int u = ID[string(a)];
			int v = ID[string(b)];
			adj[v].push_back(u);
		}
		vector<int> result;
		for (int i = 1; i <= n; ++i) {
			if (vis[i] != test) {
				topological.push_back({});
				dfs(i);
			}
		}
		int pointers[N] = {};
		while (true) {
			int mini = 1e9, chosen = -1, able = 0;
			for (int i = 0; i < topological.size(); ++i) {
				while (pointers[i] < topological[i].size() && vis[topological[i][pointers[i]]] == test) {
					++pointers[i];
				}
				if (pointers[i] < topological[i].size()) {
					++able;
					if (topological[i][pointers[i]] < mini) {
						mini = topological[i][pointers[i]];
						chosen = i;
					}
				}
			}
			if (able == 1) {
				printf("%s.\n\n", s[mini]);
				break;
			} else {
				printf("%s ", s[mini]);
			}
			vis[mini] = test;
			++pointers[chosen];
		}
		for (int i = 1; i <= n; ++i) {
			adj[i].clear();
		}
		topological.clear();
	}
	
	return 0;
}

