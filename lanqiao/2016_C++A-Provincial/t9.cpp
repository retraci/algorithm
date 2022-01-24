// 密码脱落

#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

string str;
int dp[N][N];

void solve() {
    int n = str.size();

    int mx = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[n - j]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            mx = max(mx, dp[i][j]);
        }
    }

    cout << n - mx << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> str;
    solve();

    return 0;
}