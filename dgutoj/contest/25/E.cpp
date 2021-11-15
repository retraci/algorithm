#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

#define ll long long

const ll INF = 0x3f3f3f3f;

int n;
ll g[33][33];
int vis[33];

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    int ans = INF, res = INF;
    auto dfs = [&](auto &&dfs, int u, int cnt, int sum) -> void {
        if (sum > ans) return;
        if (cnt == n - 1) {
            ans = min(ans, sum);
            return;
        }
        vis[u] = 1;
        for (int v = 1; v <= n; v++) {
            if (vis[v] || (v == n && cnt != n - 2)) continue;
            dfs(dfs, v, cnt + 1, sum + g[u][v]);
        }
        vis[u] = 0;
        return;
    };

    dfs(dfs, 1, 0, 0);
    res = min(res, ans);
    cout << res << "\n";

    return 0;
}