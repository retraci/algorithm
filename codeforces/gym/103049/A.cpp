#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 110;

int n, q;
ll va[N];
int lim;
ll f[N * N];

void work() {
    int m = 26;
    ll f[m + 1];
    for (int i = 1; i <= n; i++) f[i] = va[i];
    for (int i = n + 1; i <= m; i++) {
        f[i] = 1e18;
        for (int j = 1; j <= n; j++) {
            f[i] = min(f[i], f[i - j] + va[j]);
        }
    }

    cout << f[m] << endl;
//    for (int i = 1; i <= m; i++) cout << i << " " << f[i] << endl;
}

void init() {
    lim = n * (n - 1);
    for (int i = 1; i <= n; i++) f[i] = va[i];
    for (int i = n + 1; i <= lim; i++) {
        f[i] = 1e18;
        for (int j = 1; j <= n; j++) {
            f[i] = min(f[i], f[i - j] + va[j]);
        }
    }
}

void solve() {
//    work();

    init();
    while (q--) {
        ll K;
        cin >> K;
        if (K <= lim) {
            cout << f[K] << endl;
            continue;
        }

        ll ans = 1e18;
        for (int i = 1; i <= n; i++) {
            ll tt = K / i;
            ll rem = K % i;
            while (rem + i <= lim) {
                tt--;
                rem += i;
            }
//            cout << tt << " " << i << " " << va[i] << " " << rem << " " << f[rem] << endl;
            ans = min(ans, tt * va[i] + f[rem]);
        }
        cout << ans << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}