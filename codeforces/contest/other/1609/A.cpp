#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 20;

int n;
ll va[N], vb[N];

void solve() {
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        memcpy(vb, va, sizeof va);

        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            while (vb[j] % 2 == 0) {
                vb[j] /= 2;
                vb[i] *= 2;
            }
        }

        ll sum = 0;
        for (int j = 1; j <= n; j++) sum += vb[j];
        ans = max(ans, sum);
    }
    cout << ans << endl;
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