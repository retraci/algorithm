// 糖果

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110;
const int M = 20;
const int INF = 0x3f3f3f3f;

int n, m, K;
int va[N];
int dp[1 << M];

void solve() {
    memset(dp, INF, sizeof dp);

    int lim = 1 << m;
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        // 不选第 i 包
        for (int s = 0; s < lim; s++) dp[s] = dp[s];

        // 选第 i 包
        for (int s = 0; s < lim; s++) {
            int ns = s | va[i];
            dp[ns] = min(dp[ns], dp[s] + 1);
        }
    }

    int ans = dp[lim - 1] == INF ? -1 : dp[lim - 1];
    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> m >> K;
    for (int i = 1; i <= n; i++) {
        int s = 0;
        for (int j = 0, a; j < K; j++) {
            scanf("%d", &a);
            a--;
            s |= 1 << a;
        }
        va[i] = s;
    }
    solve();

    return 0;
}