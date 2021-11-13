#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const ll MOD = 1e9 + 7;

ll n, K;

ll ksm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    ll ans = 0, cnt = 0;
    while (K) {
        if (K & 1) ans = (ans + ksm(n, cnt)) % MOD;
        cnt++;
        K >>= 1;
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
        cin >> n >> K;
        solve();
    }

    return 0;
}