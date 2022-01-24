// 倍数问题

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;
const int MK = 1e3 + 10;

int n, K;
int va[N];
int dp[2][MK][4];
int cnt[MK];
int vb[N], tot;

void solve() {
    // 只选 3 个贪心，把每个 x = mod K   前 3 大的选出来
    sort(va + 1, va + 1 + n, greater<>());
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; i++) {
        int x = va[i] % K;
        if (cnt[x]++ < 3) vb[++tot] = va[i];
    }

    memset(dp, -0x3f, sizeof dp);
    for (int i = 0; i <= n; i++) dp[i & 1][0][0] = 0;

    for (int i = 1; i <= tot; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 1; k <= 3; k++) {
//                cout << i << " " << j << " " << k << endl;
                // 不考虑 第 i 个数
                dp[i & 1][j][k] = dp[(i - 1) & 1][j][k];

                int pj = ((j - vb[i]) % K + K) % K;
                // 考虑 第 i 个数
                dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[(i - 1) & 1][pj][k - 1] + vb[i]);
            }
        }
    }

    cout << dp[tot & 1][0][3] << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> K;
    for (int i = 1; i <= n; i++) scanf("%d", &va[i]);
    solve();

    return 0;
}