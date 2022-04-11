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
            if (get(i, j, i, j) > k) continue;

            int cc = j, cr = i;
            while (cc >= 1 && get(i, cc, i, j) <= k) cc--;
            cc++;

            while (cc <= j && cr >= 1) {
                while (cc <= j && get(cr, cc, i, j) > k) cc++;

                ll tmp = j - cc + 1;
                if (tmp <= 0) break;
                ans += tmp;
                cr--;
            }
        }
    }

    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T = 1;
//    cin >> T;
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
