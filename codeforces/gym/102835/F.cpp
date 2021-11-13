#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
vector<int> p[3 * N];
int n, m, l, r, dp[3 * N][2], fi, ans;

void dfs(int k, int fa) {
    dp[k][1] = 1, dp[k][0] = 0;
    for (int to : p[k]) {
        if (to != fa) {
            if (to == 0 && k == fi || to == fi && k == 0) continue;
            dfs(to, k);

            dp[k][0] += dp[to][1];
            dp[k][1] += min(dp[to][1], dp[to][0]);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for (int i = 1; i <= n + m; ++i) {
        cin >> l >> r;
        if (l > r) swap(l, r);
        if (l == 0 && r < n) fi = r;
        p[l].push_back(r);
        p[r].push_back(l);
    }

    dfs(0, fi);
    ans = dp[0][1];

    memset(dp, 0, sizeof(dp));
    dfs(fi, 0);
    ans = min(ans, dp[fi][1]);
    cout << ans;

    return 0;
}
