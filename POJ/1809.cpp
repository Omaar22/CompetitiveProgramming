//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
long long nCr(long long n, long long r) {
	if (n == r) return 1;
	return nCr(n - 1, r) * n / (n - r);
}
int freq[4];
long long go(int i, int j, vector<int> type) {
	int curFreq[4]{freq[0] - (type[0] == 0) - (type[1] == 0) - (type[2] == 0),
				   freq[1] - (type[0] == 1) - (type[1] == 1) - (type[2] == 1),
				   freq[2] - (type[0] == 2) - (type[1] == 2) - (type[2] == 2),
				   freq[3] - (type[0] == 3) - (type[1] == 3) - (type[2] == 3)};
	if (i == 3) {
		int x1 = type[0] / 2, y1 = type[0] % 2;
		int x2 = type[1] / 2, y2 = type[1] % 2;
		int x3 = type[2] / 2, y3 = type[2] % 2;
		return ((x1 * y2 - y1 * x2 + x2 * y3 - y2 * x3 + x3 * y1 - y3 * x1) % 2 == 0) * nCr(freq[0], curFreq[0]) *
			   nCr(freq[1], curFreq[1]) * nCr(freq[2], curFreq[2]) * nCr(freq[3], curFreq[3]);
	}
	long long ret = 0;
	for (int k = j; k < 4; ++k) {
		if (curFreq[k]) {
			type[i] = k;
			ret += go(i + 1, k, type);
		}
	}
	return ret;
}
int main() {
	int t, n;
	scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		memset(freq, 0, sizeof freq);
		scanf("%d", &n);
		while (n--) {
			int x, y;
			scanf("%d %d", &x, &y);
			int type = (abs(x) % 2) * 2 + abs(y) % 2;
			++freq[type];
		}
		vector<int> tmp(3);
		printf("Scenario #%d:\n%lld\n\n", test, go(0, 0, tmp));
	}
	return 0;
}
