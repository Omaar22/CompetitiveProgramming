/*
 * author: omar22
 * idea:
 * 		greedily insert all numbers from 1 to m into vectors of size 4
 * 		before inserting number x check if its co-prime with all numbers in his vector
 * 		if its not push it in a queue to be inserted next time
 *
 * 		greedily skip any multiple of 6 so you can use distinct multiples of 2 and 3
 * 		print the number * k
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 8e4 + 5;
vector<vector<int>> result;
bool can(int num, int i) {
	for (int j = 0; j < result[i].size(); ++j) {
		if (__gcd(result[i][j], num) != 1)
			return false;
	}
	return true;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int n, k;
	scanf("%d %d", &n, &k);
	result.resize(n);
	int cur = 1, maxi = 0;
	queue<int> q;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (cur % 6 == 0) ++cur;
			if (q.size() && can(q.front(), i)) {
				maxi = max(maxi, q.front());
				result[i].push_back(q.front());
				q.pop();
			} else if (can(cur, i)) {
				maxi = max(maxi, cur);
				result[i].push_back(cur++);
			} else {
				q.push(cur++);
				--j;
			}
		}
	}
	printf("%d\n", maxi * k);
	for (int i = 0; i < n; ++i)
		printf("%d %d %d %d\n", result[i][0] * k, result[i][1] * k, result[i][2] * k, result[i][3] * k);
	return 0;
}
