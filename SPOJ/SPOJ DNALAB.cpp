/*
	author: omar22
	idea:
 		[1] Remove all such arrays which are wholly contained within another array.
 		[2] Precalculate for each pair of indices (i, j) the maximum suffix of i that is prefix of j
 		[3] dp bitmask to minimize total cost
 		[4] build path
*/

#include <bits/stdc++.h>

using namespace std;
const int N = 101;
int n, common[15][15], target, memo[15][65536];
string after[15][15];
vector<string> a;
// [2]
int count(int i, int j) {
	vector<char> ai;
	for (int x = 0; x < a[i].size(); ++x)
		ai.push_back(a[i][x]);
	for (int startX = 0; startX < a[i].size(); ++startX) {
		vector<char> aj;
		if (ai.size() <= a[j].size()) {
			for (int y = 0; y < ai.size(); ++y)
				aj.push_back(a[j][y]);
			if (ai == aj) {
				string remJ_nonPrefix;
				for (int k = a[i].size() - startX; k < a[j].size(); ++k)
					remJ_nonPrefix += a[j][k];
				after[i][j] = remJ_nonPrefix;
				return a[i].size() - startX;
			}
		}
		ai.erase(ai.begin());
	}
	after[i][j] = a[j];
	return 0;
}
// [3]
int go(int prev, int mask) {
	if (mask == target) {
		return 0;
	}
	if (memo[prev][mask] != -1)
		return memo[prev][mask];
	int ret = 1e9;
	for (int i = 0; i < n; ++i) {
		if ((mask & (1 << i)) == 0) {
			ret = min(ret, go(i, mask | (1 << i)) + (int) a[i].size() - common[prev][i]);
		}
	}
	return memo[prev][mask] = ret;
}
// [4]
void build(int prev, int mask) {
	if (mask == target)
		return;
	string mini = "Z";
	int next = -1;
	for (int i = 0; i < n; ++i) {
		if ((mask & (1 << i)) == 0 &&
			(go(i, mask | (1 << i)) + (int) a[i].size() - common[prev][i]) == memo[prev][mask]) {
			if (mini > after[prev][i]) {
				mini = after[prev][i];
				next = i;
			}
		}
	}
	printf("%s", after[prev][next].c_str());
	build(next, mask | (1 << next));
}
// [1]
bool subset(int i, int j) {
	for (int startX = 0; startX < a[i].size(); ++startX) {
		if (startX + a[j].size() - 1 < a[i].size()) {
			bool yes = true;
			for (int k = 0; k < a[j].size(); ++k) {
				if (a[j][k] != a[i][startX + k]) {
					yes = false;
				}
			}
			if (yes) {
				return true;
			}
		}
	}
	return false;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		memset(memo, -1, sizeof memo);
		memset(common, 0, sizeof common);
		a.clear();
		target = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			char s[N];
			scanf(" %s", s);
			a.push_back(string(s));
		}
		// [1]
		for (int i = 0; i < a.size(); ++i) {
			for (int j = 0; j < a.size(); ++j) {
				if (subset(i, j) && i != j) {
					a.erase(a.begin() + j);
					--n;
					i = -1;
					break;
				}
			}
		}
		// [2]
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				common[i][j] = count(i, j);
			}
		}
		// [3]
		for (int i = 0; i < n; ++i)
			target |= (1 << i);
		int result = 1e9, index = -1;
		for (int i = 0; i < n; ++i) {
			if ((go(i, (1 << i)) + (int) a[i].size()) < result ||
				(go(i, (1 << i)) + (int) a[i].size()) == result && a[index] > a[i]) {
				result = go(i, (1 << i)) + (int) a[i].size();
				index = i;
			}
		}
		printf("Scenario #%d:\n%s", test, a[index].c_str());
		// [4]
		build(index, (1 << index));
		printf("\n\n");
	}
	return 0;
}