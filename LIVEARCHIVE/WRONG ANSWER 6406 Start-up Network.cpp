/*
 * THIS IS NOT A CORRECT ANSWER
 * todo: find whats wrong
*/


#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5, LG = 25;
int nodeID;
vector<int> adj[N];
int i, maxi, parent[N];
vector<int> freq[N];
string s;
void go(int node) {
	for (int k = 0; k < 2 - (node == 0); ++k) {
		if (s[i] == '(') {
			++nodeID;
			if (node) {
				adj[node].push_back(nodeID);
				adj[nodeID].push_back(node);
			}
			parent[nodeID] = node;
			i += 2;
			go(nodeID);
		} else {
			int cur = 0;
			bool neg = false;
			if (s[i] == '-') {
				neg = true;
				++i;
			}
			while (isdigit(s[i])) {
				cur = cur * 10 + s[i] - '0';
				++i;
			}
			++i;
			if (neg)
				cur *= -1;
			++nodeID;
			if (node) {
				adj[node].push_back(nodeID);
				adj[nodeID].push_back(node);
			}
			parent[nodeID] = node;
			if (cur >= 0)
				freq[cur].push_back(nodeID);
			maxi = max(maxi, cur);
		}
	}
	i += 2;
}
int ST[N][LG];
int lev[N];

void dfs(int idx, int l, int par) {
	ST[idx][0] = par;
	for (int i = 1; (1 << i) <= l; ++i) {
		ST[idx][i] = ST[ST[idx][i - 1]][i - 1];
	}
	lev[idx] = l;
	for (int i = 0; i < adj[idx].size(); i++) {
		int to = adj[idx][i];
		if (to != par)
			dfs(to, l + 1, idx);
	}
}

int LCA(int x, int y) {
	if (lev[x] < lev[y])swap(x, y);
	int d = lev[x] - lev[y];
	for (int i = 0; d; i++) {
		if (d & 1)x = ST[x][i];
		d >>= 1;
	}
	if (x == y)return x;
	int l = log2(lev[x]);
	for (int i = l; i >= 0; i--) {
		if (ST[x][i] != ST[y][i])
			x = ST[x][i], y = ST[y][i];
	}
	return ST[x][0];
}

int up[N], down[N];

void push(int node, int sum) {
	sum += down[node];
	down[node] = sum;
	for (auto child: adj[node]) {
		if (child != parent[node])
			push(child, sum);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int test = 1;
	while (getline(cin, s)) {
		if (s == "( )" || s == "()")
			break;
		nodeID = 0;
		maxi = 0;
		i = 0;
		go(0);
		dfs(1, 0, 0);
		for (int i = 0; i <= maxi; ++i) {
			if (freq[i].size() == 2) {
				++up[freq[i][0]];
				++up[freq[i][1]];
				up[LCA(freq[i][0], freq[i][1])] -= 2;
			} else if (freq[i].size() > 2) {
				int lca = freq[i][0];
				for (int j = 1; j < freq[i].size(); ++j) {
					lca = LCA(lca, freq[i][j]);
				}
				++down[lca];
			}
		}
		priority_queue<pair<int, pair<int, int>>> q;
		for (int i = 1; i <= nodeID; ++i) {
			if (adj[i].size() == 1 && up[i] > 0)
				q.push({lev[i], {0, i}});
		}
		
		while (q.size()) {
			auto cur = q.top();
			up[cur.second.second] += cur.second.first;
			q.pop();
			if (cur.second.second != 1)
				q.push({lev[parent[cur.second.second]], {up[cur.second.second], parent[cur.second.second]}});
		}
		push(1, 0);
		int result = 0;
		for (int i = 0; i <= nodeID; ++i)
			result = max(result, down[i] + up[i]);
		printf("Tree %d: %d\n", test++, result);
		for (int i = 1; i <= nodeID; ++i)
			adj[i].clear();
		for (int i = 0; i <= maxi; ++i)
			freq[i].clear();
		memset(up, 0, sizeof up);
		memset(down, 0, sizeof down);
		memset(ST, 0, sizeof ST);
		memset(lev, 0, sizeof lev);
	}
	return 0;
}

