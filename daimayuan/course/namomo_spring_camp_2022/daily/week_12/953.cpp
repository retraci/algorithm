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

int x, y, k;

ll work(int g, int t) {
    if ((t + y) % x != 0) return 0;

    int tmp = (t + y) / x;
    int pc = divide(tmp).size();
    return 1LL << pc;
}

void solve() {
    ll ans = 0;
    for (int i = 1; i <= k / i; i++) {
        if (k % i == 0) {
            ans += work(i, k / i);
            if (i != k / i) ans += work(k / i, i);
        }
    }
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
        cin >> x >> y >> k;
        solve();
    }

    return 0;
}