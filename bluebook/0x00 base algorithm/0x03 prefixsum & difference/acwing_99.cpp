#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;
const int maxm = 5010;

int n, r;
int g[maxm][maxm];

void solve() {
    for (int i = 1; i <= 5001; i++) {
        for (int j = 1; j <= 5001; j++) {
            g[i][j] += g[i-1][j] + g[i][j-1] - g[i-1][j-1];
        }
    }

    int ans = 0;
    for (int i = r; i <= 5001; i++) {
        for (int j = r; j <= 5001; j++) {
            ans = max(ans, g[i][j] - g[i-r][j] - g[i][j-r] + g[i-r][j-r]);
        }
    }

    cout << ans << endl;
}

int main() {
    cin >> n >> r;
    int a, b, c;
    while (n--) {
        scanf("%d%d%d", &a, &b, &c);
        g[a+1][b+1] += c;
    }
    solve();

    return 0;
}

