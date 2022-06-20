#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<ll, ll, ll, ll> tl4;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const ll MOD = 1e9 + 7;

ll n, m;
ll x1, y1, x2, y2;
ll p;

inline ll ksm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

inline ll inv(ll x) {
    return ksm(x, MOD - 2);
}

void solve() {
    ll ti = 0;
    vector<int> vis(n * m * 4);
    set<tl4> st;
    ll del1 = 1, del2 = 1;
    while (1) {
        ll nx = x1 + del1, ny = y1 + del2;
        if (nx < 1 || nx > n) del1 *= -1;
        if (ny < 1 || ny > m) del2 *= -1;

        if (st.count({x1, y1, del1, del2})) break;
        st.insert({x1, y1, del1, del2});
        if (x1 == x2 || y1 == y2) vis[ti] = 1;

        x1 += del1, y1 += del2;
        ti++;
    }

    p = p * inv(100) % MOD;
    ll E = 0, np = 1;
    for (int i = 0; i < ti; i++) {
        if (!vis[i]) continue;

        E += np * p % MOD * i % MOD;
        np *= 1 - p;
        E %= MOD, np %= MOD;
    }

    ll pt = 1 - np;
    // ans = E + (1 - pt) * (ans + t)
    ll ans = E * inv(pt) % MOD + (1 - pt) * ti % MOD * inv(pt) % MOD;
    ans = (ans % MOD + MOD) % MOD;

    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> x1 >> y1 >> x2 >> y2 >> p;
        solve();
    }

    return 0;
}