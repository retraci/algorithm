#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>

using namespace std;

#define ll long long

const int N = 510;

ll n, m, k;
ll a[N][N];

ll get(int x1, int y1, int x2, int y2) {
    return a[x2][y2] - a[x2][y1 - 1] - a[x1 - 1][y2] + a[x1 - 1][y1 - 1];
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] += a[i][j - 1] + a[i - 1][j] - a[i - 1][j - 1];
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int x = 1; x <= i; x++) {
                for (int y = 1; y <= j; y++) {
                    ll tmp = get(x, y, i, j);
                    ans += tmp <= k;
                }
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    freopen("../dp.in", "r", stdin);
    freopen("../dp.out", "w", stdout);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
            }
        }
        solve();
    }

    return 0;
}
