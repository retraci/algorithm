#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

struct Edge {
    int u, v, c;
};

const int N = 5e5 + 10;

int n, m;
vector<int> g[N];
Edge es[N];
int color[N];
int flag, cnt;

void add(int u, int eid) {
    g[u].push_back(eid);
}

int dfs(int cur, int fa, int K) {
    if (color[cur] != -1) {
        if (color[cur] != K) flag = 1;
        return 0;
    }

    color[cur] = K;
    cnt += K;
    int res = 1;
    for (auto &eid : g[cur]) {
        auto [u, v, c] = es[eid];
        if (v == cur) swap(u, v);
        if (v == fa) continue;
        int ns = c ^ K;
        res += dfs(v, u, ns);
    }

    return res;
}

void solve() {
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 1; i <= m; i++) {
        auto &[u, v, c] = es[i];
        add(u, i);
        add(v, i);
    }

    for (int i = 1; i <= n; i++) color[i] = -1;
    int ans = 0; flag = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i] != -1) continue;
        cnt = 0;
        int sum = dfs(i, 0, 0);
        ans += max(cnt, sum - cnt);
    }

    cout << (flag ? -1 : ans) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            int a, b; string c;
            cin >> a >> b >> c;
            es[i] = {a, b, c == "imposter"};
        }
        solve();
    }

    return 0;
}