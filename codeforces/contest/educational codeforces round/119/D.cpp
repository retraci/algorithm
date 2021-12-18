#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 110;

int n;
int va[N];

int calc(int c1, int c2, int x) {
    int res = 1e9;
    for (int j = 0; j <= c1; j++) {
        for (int k = 0; k <= c2; k++) {
            int rem = x - 1 * j - 2 * k;
            if (rem >= 0 && rem % 3 == 0) {
                res = min(res, rem / 3);
            }
        }
    }

    return res;
}

void solve() {
    int ans = 1e9;
    for (int c1 = 0; c1 <= 2; c1++) {
        for (int c2 = 0; c2 <= 2; c2++) {
            int mx = 0;
            for (int i = 1; i <= n; i++) {
                mx = max(mx, calc(c1, c2, va[i]));
            }

            ans = min(ans, mx + c1 + c2);
        }
    }

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
        solve();
    }

    return 0;
}