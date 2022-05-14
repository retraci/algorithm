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
#include <bitset>
#include <cassert>
#include <cmath>

using namespace std;

#define fi first
#define se second

int rnd(int mod) {
    return 1LL * rand() * rand() % mod;
}

// region 双模哈希
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;

vector<int> operator+(const vector<int> &a, const vector<int> &b) {
    int c1 = a[0] + b[0], c2 = a[1] + b[1];
    if (c1 >= mod1) c1 -= mod1;
    if (c2 >= mod2) c2 -= mod2;
    vector<int> res(2, 0);
    res[0] = c1;
    res[1] = c2;
    return res;
}

vector<int> operator-(const vector<int> &a, const vector<int> &b) {
    int c1 = a[0] - b[0], c2 = a[1] - b[1];
    if (c1 < 0) c1 += mod1;
    if (c2 < 0) c2 += mod2;
    vector<int> res(2, 0);
    res[0] = c1;
    res[1] = c2;
    return res;
}

vector<int> operator*(const vector<int> &a, const vector<int> &b) {
    vector<int> res(2, 0);
    res[0] = 1LL * a[0] * b[0] % mod1;
    res[1] = 1LL * a[1] * b[1] % mod2;
    return res;
}

vector<vector<int> > pw;
vector<int> base;

void init_hash(int lim = 0) {
    pw = vector<vector<int> >(lim + 1);
    base.resize(2);
    base[0] = rnd(mod1);
    base[1] = rnd(mod2);

    pw[0].resize(2);
    pw[0][0] = pw[0][1] = 1;
    for (int i = 1; i <= lim; i++) {
        pw[i].resize(2);
        pw[i] = pw[i - 1] * base;
    }
}
// endregion

// region 树哈希
template<int N, int M>
struct Tree_hash {
    int n, is_rand;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;
    int sz[N + 10], rd[N + 10];
    vector<int> ctr;

    Tree_hash() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;

        if (!is_rand) {
            is_rand = 1;
            for (int i = 1; i <= N; i++) rd[i] = rnd(1e9 + 7);
        }
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }

    void dfs1(int u, int fno) {
        sz[u] = 1;
        int mxs = 0;
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == fno) continue;

            dfs1(v, u);
            sz[u] += sz[v];
            mxs = max(mxs, sz[v]);
        }

        int mx = max(mxs, n - sz[u]);
        if (mx <= n / 2) ctr.push_back(u);
    }

    vector<int> dfs2(int u, int fno) {
        sz[u] = 1;

        vector<int> res(2, 1);
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == fno) continue;

            vector<int> ha = dfs2(v, u);
            sz[u] += sz[v];

            int salt = rd[sz[v]];
            vector<int> ss(2, salt);
            res = res + (ha * ss);
        }

        return res;
    }

    // 有根树哈希传入 root, 无根树不传
    vector<vector<int> > work(int rt = 0) {
        if (rt == 0) {
            fill(sz, sz + n + 1, 0);
            ctr.clear();
            dfs1(1, -1);
        } else {
            ctr.clear();
            ctr.push_back(rt);
        }

        fill(sz, sz + n + 1, 0);
        vector<int> h1 = dfs2(ctr[0], -1);
        vector<int> t(2, -1);
        vector<int> h2 = ctr.size() == 2 ? dfs2(ctr[1], -1) : t;
        if (h1 > h2) swap(h1, h2);
        vector<vector<int> > res(2);
        res[0] = h1;
        res[1] = h2;

        return res;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 3010;

int n;
string s1, s2;
Tree_hash<N, N> th;

void build(const string &s) {
    vector<int> fa(s.size() + 1);
    int cnt = 1, u = 1;
    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];
        if (ch == '0') {
            int v = ++cnt;

            th.add(u, v), th.add(v, u);

            fa[v] = u;
            u = v;
        } else {
            u = fa[u];
        }
    }
}

void solve() {
    n = 0;
    th.init(s1.size() + 1);
    build(s1);
    vector<vector<int> > h1 = th.work(1);

    n = 0;
    th.init(s2.size() + 1);
    build(s2);
    vector<vector<int> > h2 = th.work(1);

    cout << (h1 == h2 ? "same" : "different") << "\n";
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
        cin >> s1 >> s2;
        solve();
    }

    return 0;
}