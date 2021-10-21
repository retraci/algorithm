#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

string sa;

void solve() {
    int n = sa.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int j = i + 1;
        while (j < n && sa[j] == sa[i]) j++;
        ans += sa[i] == '0';

        i = j - 1;
    }

    cout << min(2, ans) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> sa;
        solve();
    }

    return 0;
}