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
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region 双模哈希
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;

pii operator+(const pii &a, const pii &b) {
    int c1 = a.fi + b.fi, c2 = a.se + b.se;
    if (c1 >= mod1) c1 -= mod1;
    if (c2 >= mod2) c2 -= mod2;
    return {c1, c2};
}

pii operator-(const pii &a, const pii &b) {
    int c1 = a.fi - b.fi, c2 = a.se - b.se;
    if (c1 < 0) c1 += mod1;
    if (c2 < 0) c2 += mod2;
    return {c1, c2};
}

pii operator*(const pii &a, const pii &b) {
    return {1LL * a.fi * b.fi % mod1, 1LL * a.se * b.se % mod2};
}
// endregion

// region 树哈希
vector<int> rd;

void init_rd(int lim) {
    rd = vector<int>(lim + 1);
    for (int i = 1; i <= lim; i++) rd[i] = rnd(1e9 + 7);
}

template<int N, class G>
struct TreeHash {
    int n;
    int sz[N + 10];
    pii ha[N + 10];
    vector<int> ctr;

    TreeHash() {}

    void dfs1(int u, int fno, const G &g) {
        sz[u] = 1;
        int mxs = 0;
        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if (v == fno) continue;

            dfs1(v, u, g);
            sz[u] += sz[v];
            mxs = max(mxs, sz[v]);
        }

        int mx = max(mxs, n - sz[u]);
        if (mx <= n / 2) ctr.push_back(u);
    }

    pii dfs2(int u, int fno, const G &g) {
        sz[u] = 1;

        pii res = {1, 1};
        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if (v == fno) continue;

            pii hash = dfs2(v, u, g);
            sz[u] += sz[v];

            int salt = rd[sz[v]];
            res = res + (hash * (pii) {salt, salt});
        }

        return ha[u] = res;
    }

    // 有根树哈希传入 root, 无根树传-1, 返回 重心 和 重心对应的哈希
    array<pair<int, pii>, 2> work(int rt, const G &g) {
        n = g.n;
        if (rt == -1) {
            fill(sz, sz + n + 1, 0);
            ctr.clear();
            dfs1(1, -1, g);
        } else {
            ctr = {rt};
        }
        if (ctr.size() != 2) ctr.push_back(-1);

        fill(sz, sz + n + 1, 0);
        pii h1 = dfs2(ctr[0], -1, g);
        pii h2 = ctr[1] != -1 ? dfs2(ctr[1], -1, g) : (pii) {-1, -1};

        return (array<pair<int, pii>, 2>) {(pair<int, pii>) {ctr[0], h1}, (pair<int, pii>) {ctr[1], h2}};
    }
};
// endregion

// region 无权图
template<int N, int M>
struct Graph {
    int n, m;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 55;

using G = Graph<N, N>;

int n, m;
vector<int> a[N];
G g;
TreeHash<N, G> th;
map<array<pii, 2>, vector<int>> cnt;

void work(int tid) {
    n = a[tid][0];
    g.init(n, -1);
    for (int i = 1; i <= n; i++) {
        if (a[tid][i]) g.add(a[tid][i], i), g.add(i, a[tid][i]);
    }

    auto [ctr1, ctr2] = th.work(-1, g);
    pii h1 = ctr1.se, h2 = ctr2.se;
    if (h1 > h2) swap(h1, h2);
    cnt[{h1, h2}].push_back(tid);
}

void solve() {
    for (int i = 1; i <= m; i++) work(i);

    vector<int> ans(m + 1);
    for (auto &[ha, vec] : cnt) {
        int mi = *min_element(vec.begin(), vec.end());
        for (int tid : vec) ans[tid] = mi;
    }

    for (int i = 1; i <= m; i++) cout << ans[i] << "\n";
}

void prework() {
    init_rd(50);
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
        cin >> m;
        for (int i = 1; i <= m; i++) {
            cin >> n;

            a[i].resize(n + 1);
            for (int j = 1; j <= n; j++) cin >> a[i][j];
            a[i][0] = n;
        }
        solve();
    }

    return 0;
}