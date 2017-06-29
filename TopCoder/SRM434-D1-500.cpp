/*
	Author: Omar22
	Idea: the result = summation of the input numbers + the maximum addition can be made by changing k digits
 		the maximum addition can be calculated by dp:
 		state: (index of digit, remaining changes)
*/

#include <bits/stdc++.h>

using namespace std;
const int N = 37;

class HexatridecimalSum {
public:
	void tailingZeros(string &a) {
		int i;
		for (i = 0; i < a.size() - 1 && a[i] == '0'; ++i);
		a.erase(a.begin(), a.begin() + i);
	}
	string add(string a, string b) {
		int extra = a.size() - b.size();
		if (b.size() < a.size())
			b = string(extra, '0') + b;
		b = string(4, '0') + b;
		extra = b.size() - a.size();
		if (b.size() > a.size())
			a = string(extra, '0') + a;
		for (int i = b.size() - 1; i >= 0; --i) {
			int digitA, digitB;
			if (isdigit(a[i]))
				digitA = a[i] - '0';
			else
				digitA = a[i] - 'A' + 10;
			if (isdigit(b[i]))
				digitB = b[i] - '0';
			else
				digitB = b[i] - 'A' + 10;
			int sum = digitA + digitB;
			if (sum < 10) {
				a[i] = '0' + sum;
			} else if (sum < 36) {
				a[i] = 'A' + sum - 10;
			} else {
				int tmp = sum % 36;
				if (tmp < 10)
					a[i] = '0' + tmp;
				else
					a[i] = 'A' + tmp - 10;
				tmp = sum / 36;
				if (isdigit(a[i - 1])) {
					if (isdigit(a[i - 1] + tmp))
						a[i - 1] += tmp;
					else
						a[i - 1] = 'A' + tmp - 10 + a[i - 1] - '0';
				} else {
					a[i - 1] += tmp;
				}
			}
		}
		return a;
	}
	vector<string> num;
	string memo[N][N];
	bool vis[N][N] = {};
	string maximum(string &a, string &b) {
		if (a.size() > b.size())
			return a;
		if (a.size() < b.size())
			return b;
		if (a > b)
			return a;
		return b;
	}
	string go(int i, int k) {
		if (i == N) {
			return "";
		}
		string &ret = memo[i][k];
		if (vis[i][k]++)
			return ret;
		ret = go(i + 1, k);
		
		if (k) {
			string extra = "0";
			for (int j = 0; j < num.size(); ++j) {
				for (int w = 0; w < num[j].size(); ++w) {
					int digit = num[j][w];
					if (isdigit(digit))
						digit -= '0';
					else
						digit = 10 + digit - 'A';
					if (digit != i)
						continue;
					string tmp(num[j].size() - w, '0');
					tmp[0] = '0' + 35 - digit;
					if (tmp[0] > '9') {
						tmp[0] = 'A' + tmp[0] - '9' - 1;
					}
					extra = add(extra, tmp);
				}
			}
			tailingZeros(extra);
			extra = add(extra, go(i + 1, k - 1));
			tailingZeros(extra);
			ret = maximum(ret, extra);
		}
		return ret;
	}
	
	string maximizeSum(vector<string> numbers, int k) {
		num = numbers;
		string sum = numbers[0];
		for (int i = 1; i < numbers.size(); ++i) {
			sum = add(sum, numbers[i]);
			tailingZeros(sum);
		}
		string ret = add(sum, go(0, k));
		tailingZeros(ret);
		return ret;
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif
	HexatridecimalSum h;
	cout << h.maximizeSum({"NO", "NO", "NO", "NO", "NO", "NO", "YES", "NO", "NO", "NO", "NO", "NO", "NO", "NO"}, 1);
	return 0;
}

