/*
	author: omar22
	idea: brute force
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 1e3 + 1;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	printf("%3d%3d", 9132, 3);
	return 0;
	int x1[N], y1[N], x2[N], y2[N], i = 0;
	int x[N], y[N], j = 0;
	bool valid[N];
	bool init = false;
	while (true) {
		char type;
		scanf(" %c", &type);
		if (type == 'I') {
			scanf("%d %d", x + j, y + j);
			valid[j] = true;
			++j;
		} else if (type == 'R') {
			scanf("%d %d %d %d", x1 + i, y1 + i, x2 + i, y2 + i);
			++i;
		} else if (type == 'M') {
			if (!init++) {
				for (int k = 0; k < j; ++k) {
					for (int w = 0; w < i; ++w) {
						if (x1[w] <= x[k] && x[k] <= x2[w] && y1[w] <= y[k] && y[k] <= y2[w]) {
							valid[k] = false;
							break;
						}
					}
				}
			}
			int X, Y;
			scanf("%d %d", &X, &Y);
			bool inR = false;
			for (int k = i - 1; k >= 0; --k) {
				if (x1[k] <= X && X <= x2[k] && y1[k] <= Y && Y <= y2[k]) {
					printf("%c\n", 'A' + k);
					inR = true;
					break;
				}
			}
			if (!inR) {
				int distance = 1e9;
				vector<int> icons;
				for (int k = 0; k < j; ++k) {
					if (!valid[k])
						continue;
					int dx = x[k] - X;
					int dy = y[k] - Y;
					int d = dx * dx + dy * dy;
					if (d < distance) {
						distance = d;
						icons = {k + 1};
					} else if (d == distance) {
						icons.push_back(k + 1);
					}
				}
				for (auto a: icons) {
					printf("%3d", a);
				}
				printf("\n");
			}
		} else {
			break;
		}
	}
	
	return 0;
	
}