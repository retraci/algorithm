#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const ll MOD = 1e9 + 7;

ll n;

void solve() {
    ll ans = 1;

    for (int i = 1; i <= 2 * n; i++) {
        if (i == 2) continue;
        ans = (ans * i) % MOD;
    }

    cout << ans << endl;
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
        cin >> n;
        solve();
    }

    return 0;
}