/*
 * author: omar22
 * idea:
 * 		dp count win / total
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 151 + 5;
int n, x;
unsigned long long memo[N][N];
unsigned long long go(int i, int sum) {
	if (i == n)
		return sum >= x;
	unsigned long long &ret = memo[i][sum];
	if (~ret)
		return ret;
	ret = 0;
	for (int j = 1; j <= 6; ++j) {
		ret += go(i + 1, sum + j);
	}
	return ret;
}
unsigned long long power(unsigned long long base, int exp) {
	unsigned long long ret = 1;
	while (exp) {
		while ((exp & 1) == 0) {
			exp /= 2;
			base *= base;
		}
		ret *= base;
		--exp;
	}
	return ret;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	while (~scanf("%d %d", &n, &x) && n + x) {
		memset(memo, -1, sizeof memo);
		unsigned long long a = go(0, 0), b = power(6, n);
		unsigned long long gcd = __gcd(a, b);
		a /= gcd;
		b /= gcd;
		if (a == 0) {
			puts("0");
		} else if (b == 1) {
			puts("1");
		} else {
			printf("%lld/%lld\n", a, b);
		}
	}
	return 0;
}
