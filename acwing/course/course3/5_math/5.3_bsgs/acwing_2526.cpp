#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

// region 扩欧
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
// endregion

// region bsgs
ll bsgs(ll a, ll b, ll m) {
    static unordered_map<ll, ll> mp;

    if (1 % m == b % m) return 0;
    mp.clear();
    ll k = sqrt(m) + 1;
    for (ll y = 0, c = b % m; y <= k - 1; y++) {
        mp[c] = y;
        c = c * a % m;
    }

    ll ak = 1;
    for (int i = 1; i <= k; i++) ak = ak * a % m;

    for (ll x = 1, c = ak; x <= k; x++) {
        if (mp.count(c)) return x * k - mp[c];
        c = c * ak % m;
    }

    return -1e18;
}
// endregion

ll ksm(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

ll inv(ll x, ll m) {
    return ksm(x, m - 2, m);
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

int m, a, b, x1, t;

void solve() {
    if (a == 0) {
        if (x1 == t) {
            cout << 1 << "\n";
        } else if (b == t) {
            cout << 2 << "\n";
        } else {
            cout << -1 << "\n";
        }
    } else if (a == 1) {
        if (b == 0) {
            cout << (t == x1 ? 1 : -1) << "\n";
        } else {
            ll x, y;
            exgcd(b, m, x, y);
            ll ans = (x * (t - x1) % m + m) % m;
            cout << ans + 1 << "\n";
        }
    } else {
        ll C = b * inv(a - 1, m) % m;
        ll A = (x1 + C) % m;
        if (A == 0) {
            ll u = (-C + m) % m;
            cout << (u == t ? 1 : -1) << "\n";
        } else {
            ll B = (t + C) % m;
            ll ans = bsgs(a, B * inv(A, m) % m, m) + 1;
            cout << (ans < 0 ? -1 : ans) << "\n";
        }
    }
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        cin >> m >> a >> b >> x1 >> t;
        solve();
    }

    return 0;
}