#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const ll MOD = 1e9 + 7;

int K;

ll ksm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

ll inv(ll a, ll p) {
    return ksm(a, p - 2);
}

ll dfs(int layer) {
    if (layer == K) return 1;

    ll son = dfs(layer + 1);
    return son * son % MOD * 4LL % MOD;
}

void solve() {
    cout << (dfs(0) * 3LL * inv(2, MOD)) % MOD << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> K;
    solve();

    return 0;
}