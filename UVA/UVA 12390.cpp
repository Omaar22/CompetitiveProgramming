/*
	Author: Omar22
	Idea: binary search on maximum number of people per box
 		for each iteration in the binary search:
 		for each i calculate b (number of boxed needed for city i) such that:
 		a[i]	   mid
		----  <=  ------
		  b         1
*/

#include <bits/stdc++.h>

using namespace std;
const int N = 5e5 + 1;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	while (true) {
		int n, m, a[N];
		scanf("%d %d", &n, &m);
		if (n == -1)
			break;
		for (int i = 0; i < n; ++i)
			scanf("%d", a + i);
		int lower = 1, upper = 1e9, result = -1e9;
		while (lower <= upper) {
			int assigned = (lower + upper) / 2;
			int sum = 0;
			for (int i = 0; i < n; ++i) {
				int b = (a[i] + assigned - 1) / assigned;
				sum += b;
			}
			if (sum <= m) {
				result = assigned;
				upper = assigned - 1;
			} else {
				lower = assigned + 1;
			}
		}
		printf("%d\n", result);
	}
	return 0;
}

