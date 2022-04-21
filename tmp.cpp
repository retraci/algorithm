#include<bits/stdc++.h>

using namespace std;
#define int long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl '\n'
#define eb emplace_back
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef double db;

const int N = 2510;
int a[N][N], f[2][10];
int K, ans = 0;

int sum(int x1, int x2, int y1, int y2) {
    return a[x2][y2] - a[x1][y2] - a[x2][y1] + a[x1][y1];
}

void slove(int x1, int x2, int y1, int y2) {
    if (x1 == x2 || y1 == y2) return;
    if (x1 + 1 == x2 && y1 + 1 == y2) {
        if (sum(x1, x2, y1, y2) == K) ans++;
        return;
    }
    if (x2 - x1 > y2 - y1) {
        int mid = x1 + x2 >> 1;
        slove(x1, mid, y1, y2);
        slove(mid, x2, y1, y2);
        for (int i = y1; i < y2; ++i) {
            f[0][0] = f[1][0] = mid;
            for (int j = 1; j <= K + 1; ++j) f[0][j] = x1, f[1][j] = x2;
            for (int j = i + 1; j <= y2; ++j) {
                for (int k = 1; k <= K + 1; k++) {
                    while (sum(f[0][k], mid, i, j) >= k) f[0][k]++;
                    while (sum(mid, f[1][k], i, j) >= k) f[1][k]--;
                }
                for (int k = 0; k <= K; ++k) {
                    ans += (f[0][k] - f[0][k + 1]) * (f[1][K - k + 1] - f[1][K - k]);
                }
            }
        }
    } else {
        int mid = y1 + y2 >> 1;
        slove(x1, x2, y1, mid);
        slove(x1, x2, mid, y2);
        for (int i = x1; i < x2; ++i) {
            f[0][0] = f[1][0] = mid;
            for (int j = 1; j <= K + 1; ++j) f[0][j] = y1, f[1][j] = y2;
            for (int j = i + 1; j <= x2; ++j) {
                for (int k = 1; k <= K + 1; k++) {
                    while (sum(i, j, f[0][k], mid) >= k) f[0][k]++;
                    while (sum(i, j, mid, f[1][k]) >= k) f[1][k]--;
                }
                for (int k = 0; k <= K; ++k) {
                    ans += (f[0][k] - f[0][k + 1]) * (f[1][K - k + 1] - f[1][K - k]);
                }
            }
        }
    }
}

signed main() {
    IOS

    int n, m;
    cin >> n >> m >> K;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char c;
            cin >> c;
            a[i][j] = c - '0';
            a[i][j] += a[i][j - 1] + a[i - 1][j] - a[i - 1][j - 1];
        }
    }
    slove(0, n, 0, m);
    cout << ans;
    return 0;
}