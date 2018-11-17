/*
 	auathor: omar22
 	idea:
 		You can observe that the bad cells from the first condition |x + y| ≡ 0 (mod 2a) are forming parallel lines with slope = -1
 		the fact that |(x)+(y)| equals |(x+1) + (y-1)| and |(x-1) + (y+1)|
 		same for the second condition but slope = 1
 		
 		Assume there was only one condition, then the answer equals the number of lines between the 2 points
 		(you can't go over the line without touching it)
 		Now with the two condition one can move few steps (without touching a bad cell) to reach
 		a cell that is bad from the first and the second condition (intersection cell)
 		
 		that makes the answer = maximum between (the number of lines between the 2 points from the first, and the second conditions)
 		
 		note handle special cases like starting point is on a bad line 
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e9;
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	long long a, b, x1, y1, x2, y2;
	scanf("%lld %lld %lld %lld %lld %lld", &a, &b, &x1, &y1, &x2, &y2);
	long long sum1 = x1 + y1, sum2 = x2 + y2;
	long long diff1 = x1 - y1, diff2 = x2 - y2;
	
	// next step is to floor division so values must be non negative with same mod value
	sum1 += N * 2 * a, sum2 += N * 2 * a, diff1 += N * 2 * b, diff2 += N * 2 * b;
	long long A1 = sum1 / (2 * a) + (sum1 % (2 * a) == 0); // number of bad lines with slope = -1 from 0 to point 1
	long long A2 = sum2 / (2 * a) + (sum2 % (2 * a) == 0); // number of bad lines with slope = -1  from 0 to point 2
	long long B1 = diff1 / (2 * b);
	long long B2 = diff2 / (2 * b);
	printf("%lld\n", max(abs(A1 - A2), abs(B1 - B2)));
	return 0;
}
