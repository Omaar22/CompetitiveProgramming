/*
	author: omar22
	idea:
 			- assume that the center of the table (the big circle) is the origin (0, 0)
 			- draw a sector that completely covers a plate (the small circle) from the center of the table
 			- calculate the angle of the drawn sector:
 			- used ternary search to find the point on a plate that is tangent to the sector (so it will completely cover the plate)
 			- if angle * n <= 360 then plates can fit on the table
 */
#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

typedef complex<double> point;

#define angle(a)                (atan2((a).imag(), (a).real()))
#define vec(a, b)                ((b)-(a))

double getAng(point A, point B, point C) // find angle abc, anticlock bc to ba
{
	double ang = angle(vec(B, C)) - angle(vec(B, A));
	if (ang - EPS < 0)
		ang += 2 * PI;
	return ang;
}
double f(double x, double h, double r) {
	double y = -sqrt(r * r - x * x) + h;
	return getAng(point(x, y), point(0, 0), point(-x, y));
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int n, R, r;
	scanf("%d %d %d", &n, &R, &r);
	double left = 0, right = r;
	double h = R - r;
	for (int i = 0; i < 200; i++) {
		double l1 = (left * 2 + right) / 3;
		double l2 = (left + 2 * right) / 3;
		if (f(l1, h, r) > f(l2, h, r)) right = l2;
		else left = l1;
	}
	double angle = f(left, h, r) * 180 / PI;
	if (angle * n > 360 + EPS || r > R) {
		puts("NO");
	} else {
		puts("YES");
	}
	return 0;
}
