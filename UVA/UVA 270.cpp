/*
	author: omar22
	Reference: drive.google.com/file/d/0B_rSt5dGmwYBR2FjVHZYVjJEMWM/view
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 1e3 + 1;

typedef complex<double> point;
const double EPS = 1e-9;
#define cp(a, b)                 ( (conj(a)*(b)).imag() )    // a*b sin(T), if zero -> parllel

bool isCollinear(point a, point b, point c) {
	return fabs(cp(b - a, c - a)) < EPS;
}

point p0, points[N];
bool cmp_smaller_angle(point p1, point p2) {
	return cp(p1 - p0, p2 - p0) < 0;
}

void find_prepare(int &n) {    // Find point with lower y then x to sort reminder points
	// around it as in grham scan.
	int i, s = 0;
	for (i = 1; i < n; i++) {
		if (points[i].imag() <= points[s].imag())
			if (points[i].imag() < points[s].imag() || points[i].real() < points[s].real())
				s = i;
	}
	p0 = points[s], points[s] = points[n - 1], points[n - 1] = p0;    //swap p0 to last elem
}


int line_points_up(int n) {
	int i, max = 2;
	if (n < 3)
		return n;
	while (n > 2) {
		find_prepare(n); // To find Next point to sort around & set it in p0
		n--;
		sort(points, points + n, cmp_smaller_angle);    // Sort them around p0
		int m = 2;    // Initial maximum
		for (i = 0; i < n - 1; i++) {
			if (isCollinear(p0, points[i], points[i + 1])) {
				m++;
			} else { /* Collection of points take another direction */
				if (m > max)
					max = m; /* save best lining up from pervious direction */
				m = 2;
			}
		}
		if (m > max)
			max = m;
	}
	return max;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d\n\n", &t);
	bool in = false;
	while (t--) {
		if (in++)
			printf("\n");
		char s[N];
		int n;
		for (n = 0;; ++n) {
			s[0] = 0;
			gets(s);
			int len = strlen(s);
			if (len == 0)
				break;
			stringstream ss(s);
			int x, y;
			ss >> x >> y;
			points[n] = point(x, y);
		}
		printf("%d\n", line_points_up(n));
	}
	return 0;
}
