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

// region 字符串哈希
vector<pii> pw;
pii base;

void init_strhash(int lim = 0) {
    pw = vector<pii>(lim + 1);
    base = {rnd(mod1), rnd(mod2)};
    pw[0] = {1, 1};
    for (int i = 1; i <= lim; i++) pw[i] = pw[i - 1] * base;
}

template<int SZ>
struct StrHash {
    pii v[SZ + 10];

    StrHash() {}

    // 下标 1 开始
    void init(const string &s) {
        int m = s.size() - 1;
        for (int j = 1; j <= m; j++) {
            char ch = s[j];
            v[j] = v[j - 1] * base + (pii) {ch, ch};
        }
    }

    pii get(int L, int R) {
        return v[R] - (v[L - 1] * pw[R - L + 1]);
    }
};
// endregion

// region 字符串最小表示法
// 下标从 0 开始
string get_min(const string &s) {
    int n = s.size();
    string ns = s + s;
    int i = 0, j = 1;

    while (i < n && j < n) {
        int k = 0;
        while (k < n && ns[i + k] == ns[j + k]) k++;
        if (ns[i + k] > ns[j + k]) i = i + k + 1;
        else j = j + k + 1;
        if (i == j) j++;
    }

    int pos = min(i, j);
    return ns.substr(pos, n);
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
