// region 欧拉序1 (2n - 1)
// 应用: lca 转 rmq问题, 维护 eula序 中dep最小的点
void dfs(int u, const G &g) {
    eula[++cnt] = u, id[u] = cnt;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (dep[v] != -1) continue;

        dep[v] = dep[u] + 1;
        dfs(v, g);
        eula[++cnt] = u;
    }
}
// endregion

// region 欧拉序2 (2n)
// 如果 u, v 有祖先关系 && ein[u] < ein[v] => [ein[u], ein[v]] 只出现1次的点, 就是 u -> v 的路径
// 如果 u, v 无祖先关系 && ein[u] < ein[v] => [eout[u], ein[v]] 只出现1次的点 + lca(u, v) 就是 u -> v 的路径
// 应用: 树上莫队
void dfs(int u, int fno) {
    eula[++cnt] = u, ein[u] = cnt;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dfs(v, u);
    }

    eula[++cnt] = u, eout[u] = cnt;
}
// endregion

// region dfs序 (n)
// 应用: 子树 => 序列
void dfs(int u, int fno) {
    id[++cnt] = u, in[u] = cnt;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dfs(v, u);
    }

    out[u] = cnt;
}
// endregion

// region dfs序: op1树链修改, op2单点查询, op3子树查询
// 维护差分, 查询 x 的子树
// op1树链修改u -> v: fw1: 维护 x, fw2: 维护 dep[u] * x
// op2单点查询x: fw1 查询 x 的子树
// op3子树查询x: fw1 查询 x 的子树 + fw2 查询 x 的子树
// fw1: 系数为 (1 - dep[u]), fw2: 系数为1
// fenwick: 单点修改, 区间查询
void add(int u, int v, int x) {
    int ca = lca.lca(u, v), caa = fa[ca];

    fw1.upd(in[u], x), fw1.upd(in[v], x);
    fw1.upd(in[ca], -x);
    if (caa != 0) fw1.upd(in[caa], -x);

    fw2.upd(in[u], 1LL * dep[u] * x), fw2.upd(in[v], 1LL * dep[v] * x);
    fw2.upd(in[ca], 1LL * dep[ca] * -x);
    if (caa != 0) fw2.upd(in[caa], 1LL * dep[caa] * -x);
}

void solve() {
    dep[rt] = 1;
    pdfs(rt, -1);

    fw1.init(n), fw2.init(n);
    lca.init(rt, g);
    vector<ll> s(n + 1);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[id[i]];

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int u, v, x;
            cin >> u >> v >> x;

            add(u, v, x);
        }
        if (op == 2) {
            int u;
            cin >> u;

            int L = in[u], R = out[u];
            ll t = a[u] + fw1.qr(R) - fw1.qr(L - 1);
            cout << t << "\n";
        }
        if (op == 3) {
            int u;
            cin >> u;

            int L = in[u], R = out[u];
            ll t = s[R] - s[L - 1]
                   + fw2.qr(R) - fw2.qr(L - 1)
                   + 1LL * (1 - dep[u]) * (fw1.qr(R) - fw1.qr(L - 1));
            cout << t << "\n";
        }
    }
}
// endregion

// region dfs序: op1单点修改, op2子树修改, op3树链查询
// 维护 u 到 root 的值, 查询 u -> v = f[u] + f[v] - f[ca] - f[caa]
// op1单点修改x: fw1: x 的子树 += v
// op2子树修改x: fw1: x 的子树 += dep[x] * v, fw2: x 的子树 += v
// op3树链查询u -> v: f[u] + f[v] - f[ca] - f[caa]
// f(int u): fw1: 系数为1, fw2: 系数为 dep[u] + 1
// fenwick: 维护差分, 区间修改, 单点查询
ll get(int u) {
    return fw1.qr(in[u]) + 1LL * (dep[u] + 1) * fw2.qr(in[u]);
}

void solve() {
    dep[rt] = 1;
    pdfs(rt, -1);

    fw1.init(n + 1), fw2.init(n + 1);
    lca.init(rt, g);
    for (int i = 1; i <= n; i++) {
        int L = in[i], R = out[i];
        fw1.upd(L, a[i]);
        fw1.upd(R + 1, -a[i]);
    }

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int u, x;
            cin >> u >> x;

            int L = in[u], R = out[u];
            fw1.upd(L, x);
            fw1.upd(R + 1, -x);
        }
        if (op == 2) {
            int u, x;
            cin >> u >> x;

            int L = in[u], R = out[u];
            fw1.upd(L, 1LL * dep[u] * -x);
            fw1.upd(R + 1, 1LL * dep[u] * x);
            fw2.upd(L, x);
            fw2.upd(R + 1, -x);
        }
        if (op == 3) {
            int u, v;
            cin >> u >> v;

            int ca = lca.lca(u, v), caa = fa[ca];
            ll t = get(u) + get(v) - get(ca) - get(caa);
            cout << t << "\n";
        }
    }
}
// endregion
