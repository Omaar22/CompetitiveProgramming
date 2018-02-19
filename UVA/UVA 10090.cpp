#include <bits/stdc++.h>

using namespace std;
const int N = 1e3 + 3;
//ax+by=gcd(a,b)
int eGCD(long long a, long long b, long long &x, long long &y) {
	x = 1;
	y = 0;
	long long nx = 0, ny = 1;
	long long t, r;
	while (b) {
		r = a / b;
		t = a - r * b;
		a = b;
		b = t;
		t = x - r * nx;
		x = nx;
		nx = t;
		t = y - r * ny;
		y = ny;
		ny = t;
	}
	return a;
}
//ax+by=c
bool solveLDE(int a, int b, int c, long long &x, long long &y, int &g) {
	g = eGCD(a, b, x, y);
	x *= c / g;
	y *= c / g;
	return (c % g) == 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int n, n1, c1, n2, c2;
	while (scanf("%d %d %d %d %d", &n, &c1, &n1, &c2, &n2) && n) {
		if (n % __gcd(n1, n2)) {
			puts("failed");
			continue;
		}
		long long lcm = 1ll * n1 * n2 / __gcd(n1, n2);
		int rem = n % lcm;
		long long x, y;
		int g;
		solveLDE(n1, n2, rem, x, y, g);
//		cout << n1 << "*" << x << " + " << n2 << "*" << y << " = " << rem << endl;
		if (x < 0) {
			long long t = (-x + lcm / n1 - 1) / (lcm / n1);
			x += lcm / n1 * t;
			y -= lcm / n2 * t;
		}
		if (y < 0) {
			long long t = (-y + lcm / n2 - 1) / (lcm / n2);
			y += lcm / n2 * t;
			x -= lcm / n1 * t;
		}
//		cout << n1 << "*" << x << " + " << n2 << "*" << y << " = " << rem << endl;
		if (1ll * c2 * n1 >= 1ll * c1 * n2) {
			x += lcm / n1 * (n / lcm);
		} else {
			y += lcm / n2 * (n / lcm);
		}
//		cout << n1 << "*" << x << " + " << n2 << "*" << y << " = " << n << endl;
		if (x < 0) {
			long long t = (-x + lcm / n1 - 1) / (lcm / n1);
			x += lcm / n1 * t;
			y -= lcm / n2 * t;
		}
		if (y < 0) {
			long long t = (-y + lcm / n2 - 1) / (lcm / n2);
			y += lcm / n2 * t;
			x -= lcm / n1 * t;
		}
//		cout << n1 << "*" << x << " + " << n2 << "*" << y << " = " << n << endl;
		if (x < 0 || y < 0) {
			puts("failed");
		} else {
			printf("%lld %lld\n", x, y);
		}
	}
	
	return 0;
}
