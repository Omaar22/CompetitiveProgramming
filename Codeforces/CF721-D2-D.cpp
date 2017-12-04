/*
 * author: omar22
 * idea:
 * 		greedily make K moves, each move pick the minimum number (as absolute value) and add or subtract x from it 
 * 		depending on the current number of negative numbers to change the sign of the product
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;

int n, k, x;
long long result[N];
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &k, &x);
	priority_queue<pair<long long, pair<bool, int>>, vector<pair<long long, pair<bool, int>>>, greater<pair<long long, pair<bool, int>>>> pq;
	bool positive = true;
	for (int i = 0; i < n; ++i) {
		int a;
		scanf("%d", &a);
		if (a < 0) {
			positive = !positive;
			pq.push({-a, {false, i}});
		} else {
			pq.push({a, {true, i}});
		}
	}
	while (k--) {
		auto cur = pq.top();
		pq.pop();
		if (cur.first == 0) {
			if (positive) {
				pq.push({x, {false, cur.second.second}});
				positive = false;
			} else {
				pq.push({x, {true, cur.second.second}});
			}
		} else {
			if (cur.second.first && positive) {
				long long next = cur.first - x;
				if (next < 0) {
					pq.push({-next, {false, cur.second.second}});
					positive = false;
				} else {
					pq.push({next, {true, cur.second.second}});
				}
			} else if (cur.second.first && !positive) {
				pq.push({cur.first + x, {true, cur.second.second}});
			} else if (!cur.second.first && positive) {
				long long next = -cur.first + x;
				if (next >= 0) {
					pq.push({next, {true, cur.second.second}});
					positive = false;
				} else {
					pq.push({-next, {false, cur.second.second}});
				}
			} else if (!cur.second.first && !positive) {
				pq.push({cur.first + x, {false, cur.second.second}});
			}
		}
	}
	while (!pq.empty()) {
		result[pq.top().second.second] = pq.top().first;
		if (!pq.top().second.first)
			result[pq.top().second.second] *= -1;
		pq.pop();
	}
	for (int i = 0; i < n; ++i)
		printf("%lld ", result[i]);
	return 0;
}
