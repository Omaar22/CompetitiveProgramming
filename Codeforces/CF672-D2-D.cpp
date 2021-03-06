/*
 * author: omar22
 * idea:
 * 		binary search on the maximum value you can take (validate by removing coins and check if its less than k)
 * 		then binary search on the minimum value you can take (validate by adding what you removed from the previous binary search)
 *
 * 		take care of case like
 * 		2 10 11
 * 		when you say the maximum is 10 you can take 2 coins not 1 making it:
 * 		4 9 10
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 5e5 + 5;
int a[N], n, k;
int brute() {
	multiset<int> st;
	for (int i = 0; i < n; ++i) {
		st.insert(a[i]);
	}
	for (int i = 0; i < k; ++i) {
		int max = *(--st.end());
		int min = *st.begin();
		st.erase(--st.end());
		st.erase(st.begin());
		st.insert(max - 1);
		st.insert(min + 1);
	}
	return *(--st.end()) - *st.begin();
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	scanf("%d %d", &n, &k);
	if (n == 1)
		return puts("0");
	long long sum = 0;
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i), sum += a[i];
//	cout << brute() << endl;
	sort(a, a + n);
	int lower = a[0], upper = a[n - 1], maxi = -1;
	while (lower <= upper) {
		int mid = (lower + upper) / 2;
		long long cost = 0;
		for (int i = 0; i < n; ++i)
			if (a[i] >= mid)
				cost += a[i] - mid;
		if (cost <= k) {
			maxi = mid;
			upper = mid - 1;
		} else {
			lower = mid + 1;
		}
	}
	long long inventory = 0;
	int extra = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] >= maxi) {
			inventory += a[i] - maxi;
			++extra;
		}
	}
	if (extra)
		--extra;
	inventory = min(1ll * k, inventory + extra);
	lower = a[0], upper = maxi;
	int mini = -1;
	while (lower <= upper) {
		int mid = (lower + upper) / 2;
		long long cost = 0;
		for (int i = 0; i < n; ++i) {
			if (a[i] < mid)
				cost += mid - a[i];
		}
		if (cost <= inventory) {
			mini = mid;
			lower = mid + 1;
		} else {
			upper = mid - 1;
		}
	}
	if (sum % n != 0)
		printf("%d\n", max(1, maxi - mini));
	else
		printf("%d\n", maxi - mini);
	return 0;
}
