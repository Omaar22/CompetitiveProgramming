#include <stdio.h>
#include <string.h>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;
const int N = 202;

int n, a[N], vis[N], visID;
char s[N], res[N];
vector<vector<int> > comp;
pair<int, int> indx[N];
void go(int node) {
	if (vis[node] == visID)
		return;
	comp.back().push_back(node);
	indx[node] = make_pair(comp.size() - 1, comp.back().size() - 1);
	vis[node] = visID;
	go(a[node]);
}
int main() {
	while (~scanf("%d", &n) && n) {
		++visID;
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) {
			if (vis[i] != visID) {
				vector<int> empty;
				comp.push_back(empty);
				go(i);
			}
		}
		int k;
		while (~scanf("%d", &k) && k) {
			gets(s);
			int len = strlen(s);
			while (len < n + 1)
				s[len++] = ' ';
			s[len] = '\0';
			strcpy(res, s);
			for (int node = 1; node <= n; ++node) {
				int i = indx[node].first, j = indx[node].second;
				j = (j + k) % comp[i].size();
				res[comp[i][j]] = s[node];
			}
			printf("%s\n", res + 1);
		}
		puts("");
	}
	return 0;
}
