/*
	author: omar22
	idea: the problem is 3 parts:
	 		area => shoelace formula
	 		lattice points inside polygon => Pick's theorem
	 		lattice points on borders => sum for each border: gcd(change in x, change in y)
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 2e2 + 1;

double polygonArea(int X[], int Y[], int n) {
	double area = 0;
	// Calculate value of shoelace formula (Gauss's area formula)
	int j = n - 1;
	for (int i = 0; i < n; i++) {
		area += (X[j] + X[i]) * (Y[j] - Y[i]);
		j = i;  // j is previous vertex to i
	}
	return abs(area / 2);
}

// Pick's theorem: A = i + b / 2 - 1
int inside(double A, int b) {
	return A - b / 2 + 1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d", &t);
	for (int test = 1; test <= t; ++test) {
		int x[N], y[N], n, onEdges = 0;
		scanf("%d", &n);
		x[0] = y[0] = 0;
		for (int i = 1; i <= n; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			x[i] = x[i - 1] + a;
			y[i] = y[i - 1] + b;
			onEdges += __gcd(abs(x[i] - x[i - 1]), abs(y[i] - y[i - 1])); // lattice points on line = gcd(change in x, change in y)
		}
		double area = polygonArea(x, y, n);
		printf("Scenario #%d:\n%d %d %.1lf\n\n", test, inside(area, onEdges), onEdges, area);
	}
	return 0;
}
