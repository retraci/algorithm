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

// region 可撤销 dsu
template<int SZ>
struct Dsu {
    vector<pii> his_fa, his_sz;
    int fa[SZ + 10], sz[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
        fill(sz, sz + _n + 1, 1);
        his_fa.clear();
        his_sz.clear();
    }

    int find(int x) {
        while (x != fa[x]) x = fa[x];
        return x;
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        if (sz[tx] > sz[ty]) swap(tx, ty);

        his_sz.push_back({ty, sz[ty]});
        sz[ty] += sz[tx];
        his_fa.push_back({tx, fa[tx]});
        fa[tx] = ty;

        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }

    void rollback(int h) {
        while (his_fa.size() > h) {
            fa[his_fa.back().fi] = his_fa.back().se;
            his_fa.pop_back();
            sz[his_sz.back().fi] = his_sz.back().se;
            his_sz.pop_back();
        }
    }

    int his() {
        return his_fa.size();
    }

    int size(int x) {
        int tx = find(x);
        return sz[tx];
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 5e5 + 10;

int n, m, q;
ai3 es[N];
vector<int> qs[N];
map<int, vector<int>> mp[N];
Dsu<N> dsu;

void solve() {
    for (int i = 1; i <= q; i++) {
        for (int eid : qs[i]) {
            int cost = es[eid][2];
            mp[cost][i].push_back(eid);
        }
    }

    vector<int> ord(m + 1);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin() + 1, ord.end(), [&](auto &lhs, auto &rhs) {
        return es[lhs][2] < es[rhs][2];
    });

    vector<int> ans(q + 1);
    dsu.init(n);
    for (int i = 1; i <= m; i++) {
        int oi = ord[i];
        for (auto &[qid, vec] : mp[es[oi][2]]) {
            int h = dsu.his();
            for (auto eid : vec) {
                auto [u, v, cost] = es[eid];
                if (dsu.same(u, v)) ans[qid] |= 1;
                dsu.unite(u, v);
            }
            dsu.rollback(h);
        }

        int j = i;
        while (j <= m) {
            int oj = ord[j];
            if (es[oj][2] != es[oi][2]) break;

            auto [u, v, cost] = es[oj];
            dsu.unite(u, v);
            j++;
        }

        i = j - 1;
    }

    for (int i = 1; i <= q; i++) {
        cout << (ans[i] ? "NO" : "YES") << "\n";
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
//    cin >> _;
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= m; i++) cin >> es[i][0] >> es[i][1] >> es[i][2];
        cin >> q;
        for (int i = 1; i <= q; i++) {
            int k;
            cin >> k;

            qs[i].resize(k);
            for (int j = 0; j < k; j++) cin >> qs[i][j];
        }
        solve();
    }

    return 0;
}