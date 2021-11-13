#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
string s;

void solve() {
    int ans = 0;

    for (int i = 0; i < n - 1; i++) {
        if (s[i] == '0') continue;
        ans += s[i] - '0' + 1;
    }

    ans += s.back() - '0';
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> s;
        solve();
    }

    return 0;
}