#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cassert>
#include <random>
#include <cmath>

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
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region 质因数分解
vector<pll> divide(ll x) {
    vector<pll> res;
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            int c = 0;
            while (x % i == 0) x /= i, c++;
            res.push_back({i, c});
        }
    }
    if (x > 1) res.push_back({x, 1});

    return res;
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

ll a, m;

ll work(ll x, const vector<pll> &fs) {
    ll s = 0;
    int lim = 1 << fs.size();
    for (int mask = 1; mask < lim; mask++) {
        ll t = 1, c = 0;
        for (int i = 0; i < fs.size(); i++) {
            if (mask >> i & 1) {
                t *= fs[i].fi;
                c++;
            }
        }

        int sgn = c & 1 ? 1 : -1;
        s += sgn * x / t;
    }

    return x - s;
}

void solve() {
    ll g = __gcd(a, m);
    ll k1 = a / g, k2 = m / g;

    auto fs = divide(k2);
    ll L = k1, R = k1 + k2 - 1;
    ll ans = work(R, fs) - work(L - 1, fs);

    cout << ans << "\n";
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
        cin >> a >> m;
        solve();
    }

    return 0;
}