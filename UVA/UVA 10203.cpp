/*
	author: omar22
	idea: the vehicle only needs to visit each road direction once so greedily calculate the sum of road lengths and divide it by 20 km/h
*/

#include <bits/stdc++.h>

using namespace std;
const int N = 101;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	int t;
	scanf("%d", &t);
	while (t--) {
		int x, y;
		double meters = 0;
		scanf("%d %d\n", &x, &y);
		while (true) {
			char s[N];
			if (gets(s) == NULL)
				break;
			if (!strlen(s))
				break;
			stringstream ss(s);
			int x1, y1, x2, y2;
			ss >> x1 >> y1 >> x2 >> y2;
			meters += hypot(x1 - x2, y1 - y2) * 2;
		}
		int minutes = round(meters / (20000 / 60.0));
		printf("%d:%.2d\n", minutes / 60, minutes % 60);
		if (t)
			printf("\n");
	}
	return 0;
}

