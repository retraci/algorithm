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

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 110;

int n;
ll va[N];

void solve() {
    {
        ll ans = va[1];
        for (int i = 1; i <= n; i += 2) ans = __gcd(ans, va[i]);
        for (int i = 2; i <= n; i += 2) {
            if (va[i] % ans == 0) ans = 1;
        }

        if (ans != 1) {
            cout << ans << "\n";
            return;
        }
    }

    {
        ll ans = va[2];
        for (int i = 2; i <= n; i += 2) ans = __gcd(ans, va[i]);
        for (int i = 1; i <= n; i += 2) {
            if (va[i] % ans == 0) ans = 1;
        }

        if (ans != 1) {
            cout << ans << "\n";
            return;
        }
    }

    cout << 0 << "\n";
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