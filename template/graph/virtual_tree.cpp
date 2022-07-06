// region 虚树
void pdfs(int u, int fno) {
    in[u] = ++ti;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        auto [v, cost] = g.e[i];
        if (v == fno) continue;

        pdfs(v, u);
    }

    out[u] = ti;
}

bool issub(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v];
}

// vs 要求不重复
void build(vector<int> &vs) {
    static vector<int> stk;
    static set<int> st;

    // 去重, 并把可能的lca都加入进 vs
    sort(vs.begin(), vs.end(), [&](auto &lhs, auto &rhs) {
        return in[lhs] < in[rhs];
    });
    st = set<int>(vs.begin(), vs.end());
    for (int i = 1; i < vs.size(); i++) {
        int gp = lca.lca(vs[i], vs[i - 1]).fi;
        st.insert(gp);
    }
    vs = vector<int>(st.begin(), st.end());
    sort(vs.begin(), vs.end(), [&](auto &lhs, auto &rhs) {
        return in[lhs] < in[rhs];
    });

    ng.edm = 0;
    for (int v : vs) ng.h[v] = -1;
    // stk 维护当前链
    stk.clear();
    for (int v : vs) {
        // 如果新点不在子树那, 那就退
        while (!stk.empty() && !issub(stk.back(), v)) stk.pop_back();

        if (!stk.empty()) {
            int cost = ???;
            ng.add(stk.back(), v, cost);
        }

        stk.push_back(v);
    }
}

void solve() {
    lca.init(n, g);
    pdfs(1, -1);

    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;

        // 当前询问的点集 vs
        vector<int> vs(k);
        for (int i = 0; i < k; i++) {
            cin >> vs[i];
            vis[vs[i]] = 1;
        }
        // 1为root
        vs.push_back(1);

        build(vs);
        dfs(1, -1);
        cout << f[1] << "\n";

        for (int x : vs) vis[x] = 0;
    }
}
// endregion
