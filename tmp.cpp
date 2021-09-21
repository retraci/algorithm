#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
int p1, q1, maxn = 1e8;
vector<int> p[3 * N];
int n, m, l, r, dp[3 * N][2], fi, ans;

void dfs(int k, int fa) {
    dp[k][1] = 1, dp[k][0] = 0;
    for (int i = 0; i < p[k].size(); ++i)
        if (p[k][i] != fa) {
            if (p[k][i] == 0 && k == fi || p[k][i] == fi && k == 0) continue;
            dfs(p[k][i], k);

            dp[k][0] += dp[p[k][i]][1];
            dp[k][1] += min(dp[p[k][i]][1], dp[p[k][i]][0]);
        }
}

void dfs1(int k, int fa) {
    dp[k][1] = 1, dp[k][0] = 0;
    for (int i = 0; i < p[k].size(); ++i)
        if (p[k][i] != fa) {
            if (p[k][i] == 0 && k == fi || p[k][i] == fi && k == 0) continue;

            dfs1(p[k][i], k);
            if (k == fi) {
                dp[k][0] = maxn;
                dp[k][1] += min(dp[p[k][i]][1], dp[p[k][i]][0]);
            } else {
                dp[k][0] += dp[p[k][i]][1];
                dp[k][1] += min(dp[p[k][i]][1], dp[p[k][i]][0]);
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
    dfs1(0, fi);
    ans = min({ans, dp[0][1], dp[0][0]});
    cout << ans;

    return 0;
}