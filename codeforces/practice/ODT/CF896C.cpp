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

// region general
#define ll long long
#define ld long double
#define ull unsigned long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;

inline void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
inline void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 1e5 + 10;

ll n, m, seed, vm;
ll a[N];

map<int, ll> odt;

ll rnd() {
    ll ret = seed;
    seed = (seed * 7 + 13) % 1000000007LL;
    return ret;
}

void get(ll &op, ll &L, ll &R, ll &x, ll &y) {
    op = (rnd() % 4) + 1;
    L = (rnd() % n) + 1;
    R = (rnd() % n) + 1;

    if (L > R) swap(L, R);

    if (op == 3) {
        x = (rnd() % (R - L + 1)) + 1;
    } else {
        x = (rnd() % vm) + 1;
    }

    if (op == 4) {
        y = (rnd() % vm) + 1;
    }
}

void split(int pos) {
    auto [L, v] = *prev(odt.upper_bound(pos));
    odt[pos] = v;
}

void assign(int L, int R, ll v) {
    split(L), split(R + 1);

    auto it = odt.find(L);
    while (it->fi != R + 1) {
        auto [tl, tv] = *it;
        it = odt.erase(it);
    }
    odt[L] = v;
}

void add(int L, int R, ll v) {
    split(L), split(R + 1);

    auto it = odt.find(L);
    while (it->fi != R + 1) {
        auto &[tl, tv] = *it;
        tv += v;

        it = next(it);
    }
}

ll query_k(int L, int R, int k) {
    split(L), split(R + 1);

    vector<pll> tmp;
    auto it = odt.find(L);
    while (it->fi != R + 1) {
        auto &[tl, tv] = *it;
        int tr = next(it)->fi - 1;
        ll sz = tr - tl + 1;
        tmp.push_back({tv, sz});

        it = next(it);
    }

    sort(tmp.begin(), tmp.end());
    int cnt = 0;
    for (auto [x, sz] : tmp) {
        cnt += sz;
        if (cnt >= k) return x;
    }

    return -1;
}

ll qsm(ll x, ll y, ll mod) {
    x %= mod;
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

ll query(int L, int R, ll x, ll y) {
    split(L), split(R + 1);

    ll res = 0;
    auto it = odt.find(L);
    while (it->fi != R + 1) {
        auto &[tl, tv] = *it;
        int tr = next(it)->fi - 1;
        ll sz = tr - tl + 1;
        res += sz * qsm(tv, x, y) % y;
        res %= y;

        it = next(it);
    }
    return res;
}

void solve() {
    odt[1] = 0;
    for (int i = 1; i <= n; i++) {
        assign(i, i, a[i]);
    }

    while (m--) {
        ll op, L, R, x, y;
        get(op, L, R, x, y);

        if (op == 1) {
            add(L, R, x);
        } else if (op == 2) {
            assign(L, R, x);
        } else if (op == 3) {
            cout << query_k(L, R, x) << "\n";
        } else {
            cout << query(L, R, x, y) << "\n";
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
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n >> m >> seed >> vm;
        for (int i = 1; i <= n; i++) a[i] = (rnd() % vm) + 1;
        solve();
    }

    return 0;
}