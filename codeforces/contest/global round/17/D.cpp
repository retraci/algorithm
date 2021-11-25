#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;
const ll MOD = 1e9 + 7;

int n;
ll va[N];
ll r[N], f[N];
ll c[31];

ll qsm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return qsm(x, MOD - 2);
}

ll C(ll a, ll b) {
    return f[a] * inv(f[a - b]) % MOD * inv(f[b]) % MOD;
}

void init() {
    r[0] = 1;
    for (int i = 1; i <= n; i++) r[i] = (r[i - 1] * 2) % MOD;
    f[0] = 1;
    for (int i = 1; i <= n; i++) f[i] = (f[i - 1] * i) % MOD;
}

ll get(ll x) {
    ll res = 0;
    while (!(x & 1)) res++, x >>= 1;
    return res;
}

void solve() {
    init();

    for (int i = 1; i <= n; i++) c[get(va[i])]++;

    ll ans = r[n] - 1;
    for (int i = 1; i < 31; i++) {
        ll tt = 0;
        for (int j = i + 1; j < 31; j++) tt += c[j];
        for (int j = 1; j <= c[i]; j += 2) {
            ans -= C(c[i], j) * r[tt] % MOD;
            ans = (ans + MOD) % MOD;
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}