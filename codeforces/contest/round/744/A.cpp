#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

string str;

void solve() {
    int cnt[5] = {0};
    for (char ch : str) {
        cnt[ch - 'A']++;
    }

    cout << ((cnt[1] == cnt[0] + cnt[2]) ? "YES" : "NO") << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> str;
        solve();
    }

    return 0;
}