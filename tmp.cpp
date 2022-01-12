#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <climits>

using namespace std;
const int maxn = 500 + 5;
long long a[maxn], s[maxn];
long long dp[505][505], idx[505][505];

int main() {
    int t = 1;
    while (t--) {
        int n, l, k;
        cin >> n >> l >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> s[i];
        memset(dp, 0x3f, sizeof(dp));
        memset(idx, -1, sizeof(idx));
        dp[0][0] = 0, idx[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                if (j == 0) {
                    dp[i][j] = dp[i - 1][j] + (a[i] - a[idx[i - 1][j]]) * s[idx[i - 1][j]];
                    idx[i][j] = i;
                } else {
                    long long ans;
                    if (idx[i - 1][j] != -1) {
                        ans = dp[i - 1][j] + (a[i] - a[idx[i - 1][j]]) * s[idx[i - 1][j]];
                        if (dp[i][j] > ans) {
                            dp[i][j] = ans;
                            idx[i][j] = i;
                        }
                    }
                    if (idx[i - 1][j - 1] != -1) {
                        ans = dp[i - 1][j - 1] + (a[i] - a[idx[i - 1][j - 1]]) * s[idx[i - 1][j - 1]];
                        if (dp[i][j] > ans) {
                            dp[i][j] = ans;
                            idx[i][j] = idx[i - 1][j - 1];
                        }
                    }
                }
            }
        }
        long long ans = LLONG_MAX;
        for (int i = 0; i <= k; i++) {
            ans = min(ans, dp[n][i] + (l - a[idx[n][i]]) * s[idx[n][i]]);
        }
        cout << ans << "\n";
    }
    return 0;
}