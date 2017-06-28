/*
	Author: Omar22
	
	Idea:
 		- Just compare the two probabilities.
 		  The probability of finding a zero, and the probability of shooting 2 consecutive zeros.
		
 		number of zeros		number of zeros followed by another zero
		--------------	  ?    ----------------------------------------
		      n		         	  number of zeros
*/

#include <bits/stdc++.h>

using namespace std;
const int N = 1e2 + 1;


int cmp(pair<int, int> a, pair<int, int> b) {
	if (a.first * b.second == b.first * a.second)
		return 0;
	if (a.first * b.second < b.first * a.second)
		return 1;
	return -1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	char s[N];
	while (scanf("%s", s) != EOF) {
		int n = strlen(s), zeros = 0, live = 0;
		for (int i = 0; i < n; ++i) {
			zeros += s[i] == '0';
			if (s[i] == '0') {
				if (s[(i + 1) % n] == '0')
					++live;
			}
		}
		if (cmp({zeros, n}, {live, zeros}) == 0) {
			printf("EQUAL\n");
		} else if (cmp({zeros, n}, {live, zeros}) == 1) {
			printf("SHOOT\n");
		} else {
			printf("ROTATE\n");
		}
	}
	return 0;
}

