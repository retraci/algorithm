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
vector<pll> fs;

void divide(ll x) {
    fs = {};
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            int c = 0;
            while (x % i == 0) x /= i, c++;
            fs.push_back({i, c});
        }
    }
    if (x > 1) fs.push_back({x, 1});
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

ll L, R, n;
int ca;

ll work(ll x) {
    ll res = x;
    int cnt = fs.size();
    int lim = 1 << cnt;
    for (int mask = 1; mask < lim; mask++) {
        ll t = 1, c = 0;
        for (int i = 0; i < cnt; i++) {
            if (mask >> i & 1) {
                t *= fs[i].fi;
                c++;
            }
        }

        int sign = c & 1 ? -1 : 1;
        res += sign * x / t;
    }

    return res;
}

void solve() {
    divide(n);
    ll ans = work(R) - work(L - 1);

    static char buf[110];
    sprintf(buf, "Case #%d: %lld", ++ca, ans);
    cout << string(buf) << "\n";
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
        cin >> L >> R >> n;
        solve();
    }

    return 0;
}