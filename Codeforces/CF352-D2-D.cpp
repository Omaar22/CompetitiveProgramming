/*
 * author: omar22
 * idea:  I HAVE NO IDEA WHY!
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 4e3 + 5;
int n, a[N], target;
int calc() {
	int ret = 0;
	vector<int> v(a, a + n + 1);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (v[j] == i) {
				v.erase(v.begin() + j);
				v.insert(v.begin() + i, i);
				ret += j - i;
				break;
			}
		}
	}
	return ret;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	target = calc();
	printf("%d\n", target * 2 - (target % 2));
	return 0;
}
