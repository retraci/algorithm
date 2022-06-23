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

// region exbsgs
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

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

ll exbsgs(ll a, ll b, ll m) {
    b = (b % m + m) % m;
    if (1 % m == b % m) return 0;
    ll d = __gcd(a, m);
    if (d == 1) return bsgs(a, b, m);

    if (b % d) return -1e18;
    ll x, y;
    exgcd(a / d, m / d, x, y);
    return exbsgs(a, b / d * x % (m / d), m / d) + 1;
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

int a, b, p;

void solve() {
    ll ans = exbsgs(a, b, p);
    if (ans < 0) cout << "No Solution" << "\n";
    else cout << ans << "\n";
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
//    cin >> _;
    while (cin >> a >> p >> b, a) {
        solve();
    }

    return 0;
}