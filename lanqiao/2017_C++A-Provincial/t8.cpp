// 包子凑数

#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int n;
int va[N];
int dp[N * N];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

void solve() {
    int gcdnum = va[0];
    for (int i = 1; i < n; i++) {
        gcdnum = gcd(gcdnum, va[i]);
    }
    if (gcdnum > 1) {
        puts("INF");
        return;
    }

    memset(dp, 0, sizeof dp);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = va[i]; j <= 10000; j++) {
            if (dp[j - va[i]]) dp[j] = 1;
        }
    }

    int ans = 0;
    for (int i = 0; i <= 10000; i++) if (dp[i] == 0) ans++;

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> va[i];
    solve();

    return 0;
}