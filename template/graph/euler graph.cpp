// region 有向图欧拉回路
vector<int> g[N];
int in[N], out[N];
vector<vector<int>> ans;

void add(int u, int v) {
    g[u].push_back(v);
    in[v]++, out[u]++;
}

void dfs(int u) {
    while (!g[u].empty()) {
        int v = g[u].back();
        g[u].pop_back();
        dfs(v);
        ans.push_back({u, v});
    }
}
// endregion

// region 无向图欧拉回路
set<int> g[N];
int du[N];
vector<int> ans;
map<pii, int> cnt;

void add(int u, int v) {
    g[u].insert(v);
    cnt[{u, v}]++;
    du[v]++;
}

void dfs(int u) {
    for (auto v : g[u]) {
        if (cnt[{u, v}]) {
            cnt[{u, v}]--, cnt[{v, u}]--;
            dfs(v);
        }
    }
    ans.push_back(u);
}
// endregion

void solve() {
    int s = 0;
    for (int i = 1; i < N; i++) {
        if (du[i] & 1) {
            s = i;
            break;
        }
    }
    if (s == 0) s = 1;

    dfs(s);
    reverse(ans.begin(), ans.end());
    for (int x : ans) cout << x << "\n";
}