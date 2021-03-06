/*
author: omar22
idea:
- compress original string to another string where no 2 consecutive characters are equal
- calculate the frequency of each character of the compressed string
- assume the following:
	- loop for each index i:
		- loop for each index j greater than i:
			- if compressed[j] == compressed[i] then the substring from i to j is a palindrome (in the compressed string)
			  you need to count the number of substring in the original string making this compressed string
			- the total number those substrings = freq[i] * freq[j]
			- if freq[i] * freq[j] is even then exactly half of them is even length and half of them is odd length 
			- otherwise (freq[i] * freq[j] - 1) / 2 is even lengths and (freq[i] * freq[j] - 1) / 2 is odd lengths
			- now only one substring left uncalculated this string could be even or odd length 
			  depending on sum of frequencies between i and j (inclusive)
			- if the sum of frequencies is even then that substring is even length otherwise it is odd
- doing too many cumulative arrays of frequencies of each type would help calculate for each j without loop
- then for each single character in the compressed string calculate the even/odd substrings 

*time complexity O(n)
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 3;

char s[N], unq[N];
int freq[N];                              //  freq[i] even/odd
int totalFreq[N];                         // cumulative of freq
int cumFreq[N][2][2];    // cumulative sum of freq [a/b] [even odd of freq at i]
int cumCnt[N][2][2];    // cumulative sum of count [a/b] [even odd of freq at i]
int cumOddCnt[N][2][2];    // cnt of (odd freq at i), [a/b] [even odd of cumulative frequency till i]
int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	scanf("%s", s + 1);
	int n = strlen(s + 1), m = 0;
	for (int i = 1; i <= n; ++i) {
		int j = i;
		++m;
		while (j <= n && s[j] == s[i]) {
			++j;
			++freq[m];
		}
		unq[m] = s[i];
		i = j - 1;
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
				cumFreq[i][j][k] = cumFreq[i - 1][j][k], cumCnt[i][j][k] = cumCnt[i - 1][j][k], cumOddCnt[i][j][k] = cumOddCnt[i - 1][j][k];
		
		cumFreq[i][unq[i] - 'a'][freq[i] % 2] += freq[i];
		cumCnt[i][unq[i] - 'a'][freq[i] % 2]++;
		
		totalFreq[i] = totalFreq[i - 1] + freq[i];
		if (freq[i] % 2) {
			cumOddCnt[i][unq[i] - 'a'][totalFreq[i] % 2]++;
		}
	}
	
	long long even = 0, odd = 0;
	for (int i = 1; i <= m; ++i) {
		if (freq[i] % 2 == 0) { // l even
			long long subs = 1LL * freq[i] * (cumFreq[m][unq[i] - 'a'][0] - cumFreq[i][unq[i] - 'a'][0]
											  + cumFreq[m][unq[i] - 'a'][1] - cumFreq[i][unq[i] - 'a'][1]);
			even += subs / 2;
			odd += subs / 2;
		} else {
			// l odd r even
			long long subs = 1LL * freq[i] * (cumFreq[m][unq[i] - 'a'][0] - cumFreq[i][unq[i] - 'a'][0]);
			even += subs / 2;
			odd += subs / 2;
			
			// l odd r odd
			subs = 1LL * freq[i] * (cumFreq[m][unq[i] - 'a'][1] - cumFreq[i][unq[i] - 'a'][1]) -
				   (cumCnt[m][unq[i] - 'a'][1] - cumCnt[i][unq[i] - 'a'][1]);
			even += subs / 2;
			odd += subs / 2;
			if (totalFreq[i] % 2) {
//				cnt of r (odd freq) and cum[r] - cum[l] is even
				even += cumOddCnt[m][unq[i] - 'a'][0] - cumOddCnt[i][unq[i] - 'a'][0];
//				cnt of r (odd freq) and cum[r] - cum[l] is odd
				odd += cumOddCnt[m][unq[i] - 'a'][1] - cumOddCnt[i][unq[i] - 'a'][1];
			} else {
//				cnt of r (odd freq) and cum[r] - cum[l] is even
				even += cumOddCnt[m][unq[i] - 'a'][1] - cumOddCnt[i][unq[i] - 'a'][1];
//				cnt of r (odd freq) and cum[r] - cum[l] is odd
				odd += cumOddCnt[m][unq[i] - 'a'][0] - cumOddCnt[i][unq[i] - 'a'][0];
			}
		}
	}
	for (int i = 1; i <= m; ++i) {
		long long total = 1LL * freq[i] * (freq[i] + 1) / 2;
		int oddIdx = (freq[i] + 1) / 2;
		long long oddIdxCnt = 1LL * oddIdx * oddIdx;
		if (freq[i] % 2 == 0) {
			even += oddIdxCnt;
			odd += total - oddIdxCnt;
		} else {
			odd += oddIdxCnt;
			even += total - oddIdxCnt;
		}
	}
	printf("%lld %lld\n", even, odd);
	return 0;
}
