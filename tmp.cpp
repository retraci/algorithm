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
#include <cmath>

#define pb push_back
#define MaxN 10500
using namespace std;
vector<int> g[MaxN], p[MaxN];
int cnt, s[MaxN], sp, ans[MaxN], tn;
bool dis[MaxN], vis[MaxN], e[MaxN];

void pfs(int u) {
    vis[u] = 1;
    for (int i = 0, v; i < g[u].size(); i++)
        if (!vis[v = g[u][i]]) {
            dis[v] = dis[u] ^ 1;
            e[p[u][i]] = 1;
            pfs(v);
        } else if (!e[p[u][i]]) {
            e[p[u][i]] = 1;
            if (dis[u] == dis[v]) {
                cnt++;
                s[u]++;
                s[v]--;
                sp = p[u][i];
            } else {
                s[u]--;
                s[v]++;
            }
        }
}

void dfs(int u) {
    vis[u] = 1;
    for (int i = 0, v; i < g[u].size(); i++)
        if (!vis[v = g[u][i]]) {
            dfs(v);
            if (s[v] == cnt)ans[++tn] = p[u][i];
            s[u] += s[v];
        }
}

int n, m;

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        g[u].pb(v);
        p[u].pb(i);
        g[v].pb(u);
        p[v].pb(i);
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i])pfs(i);

    for (int i = 1; i <= n; i++) cout << s[i] << " ";
    cout << "\n";

    if (!cnt) {
        printf("%d\n", m);
        for (int i = 1; i <= m; i++)
            printf("%d ", i);
        return 0;
    }
    for (int i = 1; i <= n; i++)vis[i] = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i])dfs(i);
    if (cnt == 1)ans[++tn] = sp;
    printf("%d\n", tn);
    sort(ans + 1, ans + tn + 1);
    for (int i = 1; i <= tn; i++)
        printf("%d ", ans[i]);
    return 0;
}