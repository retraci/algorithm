#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 1e5 + 10;
const ll MOD = 1e9 + 9;

ll n;
ll ps[N];
ll fac[N], f[N], inv[N];
int vis[N];
vector<ll> ls;

ll ksm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
    f[1] = 1;
    for (int i = 2; i < N; i++) f[i] = ksm(i, i - 2);
    for (int i = 0; i < N; i++) inv[i] = ksm(fac[i], MOD - 2);
}

ll dfs(int u) {
    vis[u] = 1;
    int v = ps[u];
    if (vis[v]) return 1;
    return dfs(v) + 1;
}

void solve() {
    for (int i = 1; i <= n; i++) vis[i] = 0;
    ls = {};
        for (int i = 1; i <= n; i++) {
        if (!vis[i]) ls.push_back(dfs(i));
    }

    ll ans = fac[n - ls.size()];
    for (ll k : ls) {
        ans = ans * f[k] % MOD * inv[k - 1] % MOD;
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    init();
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> ps[i];
        solve();
    }

    return 0;
}