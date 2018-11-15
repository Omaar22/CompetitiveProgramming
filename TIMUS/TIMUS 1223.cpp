/*
 	author: omar22
 	idea:
 		assume the following
 		dp(number of search floors, remaining eggs):
			loop for each floor, try drop egg from that floor, assume it will break and assume it will not,
			the worst case is the maximum of them, minimize the worst case
			
		Good observation: if the number of eggs >= log2(number of floors) then an optimal solution will be simulating binary search,
		so for the worst case you need at most log2(number of floors) 
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 3;
int mem[N][11];
int go(int floor, int eggs) {
	if (floor == 0)
		return 0;
	if (eggs == 0)
		return 1e9;
	int &ret = mem[floor][eggs];
	if (~ret)
		return ret;
	ret = 2e9;
	for (int i = 1; i <= floor; ++i) { // drop egg from floor i
		ret = min(ret,
				  1 + max(go(i - 1, eggs - 1), // egg broken then last good floor is one of the i - 1 below floors
						  go(floor - i, eggs))); // egg not broken then the last good floor is one of the floors above i (floor - i)
	}
	return ret;
}
int main() {
//#ifndef ONLINE_JUDGE
//	freopen("input.in", "r", stdin);
//#endif
	int t;
	memset(mem, -1, sizeof mem);
	int n, e;
	while (~scanf("%d %d", &e, &n) && n + e) {
		e = min(e, 10);
		printf("%d\n", go(n, e));
	}
	return 0;
}
