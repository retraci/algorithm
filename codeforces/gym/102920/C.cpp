#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_set>

using namespace std;

typedef pair<int, int> pii;

const int N = 100010;

int n, m;
vector<pii> g[N];
int pcs[N];
unordered_set<int> s1, st;
int vis[N];

void add(int u, int v, int w) {
    g[u].push_back({v, w});
}

int dfs(int u, int fa) {
    int flag = s1.count(u);
    for (auto &[v, w]: g[u]) {
        if (v == fa) continue;
        flag |= dfs(v, u);
    }

    if (flag) st.insert(u);
    return flag;
}

void solve() {
    for (int i = 1; i <= m; i++) s1.insert(pcs[i]);
    dfs(pcs[1], 0);

    cout << st.size() << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    for (int i = 1; i <= m; i++) {
        int a;
        cin >> a;
        pcs[i] = a;
    }
    solve();

    return 0;
}