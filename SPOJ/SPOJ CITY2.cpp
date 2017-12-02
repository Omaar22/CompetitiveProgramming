/*
	author: omar22
	idea:
        greedly handle the 3 cases:
        * if the height of building i == height of building i - 1 then its the same building
        * if the height of building i >  height of building i - 1 then its diffrent building
        * if the height of building i <  height of building i - 1 then 
            - if there is building j (j < i) such that a[j] == a[i] 
              and there is no building k (j < k < i) with height a[k] < a[i] then its the same building
            - else its a new building
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;

int a[N],n, test;
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        int result = 0;
        set<int> st;
        for (int i = 1; i <= n; ++i) {
            if (a[i] > a[i - 1]) {
                ++result;
                st.insert(a[i]);
            } else if (a[i] < a[i - 1]) {
                if (a[i] && st.find(a[i]) == st.end())
                    ++result;
                auto it = st.insert(a[i]).first;
                ++it;
                st.erase(it, st.end());
            }
        }
        printf("Case %d: %d\n", ++test, result);
    }

    return 0;
}

