/*
  author: omar22
  idea:
    Manhattan 2D Rotation problem
    After converting each (x, y) to (x+y, x-y) the distance between two point (x1', y1') and (x2', y2') will 
    equal (abs(x1' - x2') + abs(y1' - y2')) / 2
    Can be calculated by commulative sum of Xs after sorting on X and Ys after sorting on Y
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 3;
struct P {
	long long x, y, sumX, sumY;
} p[N];

long long cumX[N], cumY[N];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		p[i].x = a + b;
		p[i].y = a - b;
	}
	sort(p + 1, p + n + 1, [](P a, P b){
		return a.x < b.x;
	});
	for (int i = 1; i <= n; ++i)
		cumX[i] = cumX[i - 1] + p[i].x;
	for (int i = 1; i <= n; ++i)
		p[i].sumX = p[i].x * i - cumX[i] + cumX[n] - cumX[i] - p[i].x * (n - i);
	sort(p + 1, p + n + 1, [](P a, P b){
		return a.y < b.y;
	});
	for (int i = 1; i <= n; ++i)
		cumY[i] = cumY[i - 1] + p[i].y;
	for (int i = 1; i <= n; ++i)
		p[i].sumY = p[i].y * i - cumY[i] + cumY[n] - cumY[i] - p[i].y * (n - i);
	long long res = 1e18;
	for (int i = 1; i <= n; ++i)
		res = min(res, p[i].sumX + p[i].sumY);
	printf("%lld\n", res / 2);
	return 0;
}


