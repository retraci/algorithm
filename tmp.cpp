#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;

#define ll long long

const int N = 1010;
const ll MOD = 1e9 + 7;

ll n;
ll f[N][N];

void solve() {
    f[0][0] = 1;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= n / 2; j++) {
            f[i][j] = (f[i][j] + f[i - 1][j]) % MOD;
            f[i][j] = (f[i][j] + f[i - 1][j - 1]) % MOD;
        }
    }

    cout << 2 * f[n - 1][n / 2] << endl;
}

const int MAXN = 22;

int low[MAXN], dfn[MAXN], iscut[MAXN], dfs_clock;
bool isbridge[MAXN];
int cnt_bridge;
int father[MAXN];

int T;
int m;
vector<int> g[N];

void tarjan(int u, int fa) {
    father[u] = fa;
    low[u] = dfn[u] = ++dfs_clock;

    cout << u << " " << dfn[u] << " " << low[u] << endl;

    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                isbridge[v] = true;
                ++cnt_bridge;
            }
        } else if (dfn[v] < dfn[u] && v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void add(int u, int v) {
    g[u].push_back(v);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    while (cin >> n >> m, n) {
        while (m--) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        tarjan(1, 0);
    }
    cout << cnt_bridge << endl;

    return 0;
}