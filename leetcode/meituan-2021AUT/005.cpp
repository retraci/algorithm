#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;


#define ll long long

const int N = 2010;
const ll MOD = 1e9 + 7;

int n, K;
vector<int> g[N];
int level[N];
int vis[N];

void addEdge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
}

ll dfs(int root, int src) {
    ll res = 1;
    vis[root] = 1;

    for (int i = 0; i < g[root].size(); i++) {
        int cur = g[root][i];
        if (vis[cur]) continue;
        if (level[cur] > level[src] && level[cur] - level[src] <= K || level[cur] == level[src] && cur > src) {
            res = res * (dfs(cur, src) + 1) % MOD;
        }
    }

    return res;
}

void solve() {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        memset(vis, 0, sizeof vis);
        ans = (ans + dfs(i, i)) % MOD;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> K;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;
        addEdge(b, a);
        addEdge(a, b);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &level[i]);
    }
    solve();

    return 0;
}