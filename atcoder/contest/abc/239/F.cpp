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

int n, m;
int a[N];
pii es[N];
Dsu<N> dsu;

void solve() {
    dsu.init(n);
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        a[u]--, a[v]--;
        dsu.unite(u, v);
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] < 0) {
            cout << -1 << "\n";
            return;
        }
    }

    vector<int> b[n + 1];
    for (int i = 1; i <= n; i++) {
        while (a[i]--) b[dsu.find(i)].push_back(i);
    }

    int f0 = 0, f1 = 0;
    for (int i = 1; i <= n; i++) {
        if (b[dsu.find(i)].size() == 0) f0 = 1;
        if (b[dsu.find(i)].size() > 0) f1 = 1;
    }
    if (f0 && f1) {
        cout << -1 << "\n";
        return;
    }

    vector<pii> ans;
    vector<int> c1, c2;
    for (int i = 1; i <= n; i++) {
        int tx = dsu.find(i);
        if (b[tx].size() < 2) {
            if (b[tx].size() == 1) c1.push_back(b[tx][0]);
            b[tx] = {};
            continue;
        }

        if (c2.empty()) {
            for (int x : b[tx]) c2.push_back(x);
            b[tx] = {};
            continue;
        }
        int u = c2.back(); c2.pop_back();
        int v = b[tx].back(); b[tx].pop_back();
        ans.push_back({u, v});
        for (int x : b[tx]) c2.push_back(x);
        b[tx] = {};
    }

    if (c1.size() == 2 && c2.size() == 0) {
        cout << c1[0] << " " << c1[1] << "\n";
        return;
    }

    if (c1.size() != c2.size()) {
        cout << -1 << "\n";
        return;
    }

    for (int i = 0; i < c1.size(); i++) {
        ans.push_back({c1[i], c2[i]});
    }
    for (auto [x, y] : ans) cout << x << " " << y << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) cin >> es[i].fi >> es[i].se;
        solve();
    }

    return 0;
}