#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 50010;

ll n, x;
ll va[N];

void solve() {
    ll f[n + 1][2][2];
    memset(f, 0, sizeof f);

    f[1][0][1] = 1;
    for (int i = 2; i <= n; i++) {
        // 不选
        f[i][0][0] = max(f[i - 1][0][0], f[i - 1][1][0]);
        f[i][1][0] = max(f[i - 1][0][1], f[i - 1][1][1]);
        // 选
        f[i][0][1] = max(f[i - 1][0][0], f[i - 1][1][0]) + 1;
        if (i - 1 >= 1 && va[i] + va[i - 1] >= 2 * x) {
            f[i][1][1] = f[i - 1][0][1] + 1;
            if (i - 2 >= 1 && va[i] + va[i - 1] + va[i - 2] >= 3 * x) {
                f[i][1][1] = max(f[i][1][1], f[i - 1][1][1] + 1);
            }
        }
    }

    ll ans = *max_element(&f[n][0][0], &f[n][1][2]);
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        cin >> x;
        solve();
    }

    return 0;
}