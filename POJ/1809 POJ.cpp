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
		long long res = 0;
		for (int type1 = 0; type1 < 4; ++type1) {
			for (int type2 = type1; type2 < 4; ++type2) {
				for (int type3 = type2; type3 < 4; ++type3) {
					int curFreq[4]{freq[0] - (type1 == 0) - (type2 == 0) - (type3 == 0),
								   freq[1] - (type1 == 1) - (type2 == 1) - (type3 == 1),
								   freq[2] - (type1 == 2) - (type2 == 2) - (type3 == 2),
								   freq[3] - (type1 == 3) - (type2 == 3) - (type3 == 3)};
					int x1 = type1 / 2, y1 = type1 % 2;
					int x2 = type2 / 2, y2 = type2 % 2;
					int x3 = type3 / 2, y3 = type3 % 2;
					res += ((x1 * y2 - y1 * x2 + x2 * y3 - y2 * x3 + x3 * y1 - y3 * x1) % 2 == 0) *
						   nCr(freq[0], curFreq[0]) * nCr(freq[1], curFreq[1]) * nCr(freq[2], curFreq[2]) *
						   nCr(freq[3], curFreq[3]);
					
				}
			}
		}
		printf("Scenario #%d:\n%lld\n\n", test, res);
	}
	return 0;
}
