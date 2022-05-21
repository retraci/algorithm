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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region dsu
template<int SZ>
struct Dsu {
    int fa[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        fa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion


const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;
const int MOD = 998244353;

int n, m;
pii es[N];
Dsu<N> dsu;

int ksm(int v, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res = 1LL * res * v % MOD;
        v = 1LL * v * v % MOD;
        k >>= 1;
    }

    return res;
}

void solve() {
    dsu.init(n);
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        dsu.unite(u, v);
    }

    vector<int> ce(n + 1), cv(n + 1);
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        int tu = dsu.find(u);
        ce[tu]++;
    }
    for (int i = 1; i <= n; i++) {
        int tx = dsu.find(i);
        cv[tx]++;
    }

    for (int i = 1; i <= n; i++) {
        int tx = dsu.find(i);

        if (ce[tx] != cv[tx]) {
            cout << 0 << "\n";
            return;
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += dsu.find(i) == i;
    }
    cout << ksm(2, cnt) << "\n";
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
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> es[i].fi >> es[i].se;
        solve();
    }

    return 0;
}