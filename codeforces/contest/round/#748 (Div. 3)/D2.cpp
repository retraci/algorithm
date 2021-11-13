#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 44, M = 2e6 + 10;

int n;
int va[N], vb[N];
int cnt[M];

void work(ll x) {
    for (ll i = 1; i * i <= x; i++) {
        if (x % i != 0) continue;
        ll a = i, b = x / i;
        if (a == b) cnt[a]++;
        else cnt[a]++, cnt[b]++;
    }
}

void solve() {
    sort(va, va + n);

    int ans = -1;
    for (int k = 0; k < n; k++) {
        for (int i = k + 1; i < n; i++) vb[i] = va[i] - va[k];

        int p = k + 1;
        while (p < n && vb[p] == 0) p++;
        int c0 = p - k;
        if (c0 > n / 2) {
            cout << -1 << endl;
            return;
        }

        for (int i = 1; i <= vb[n - 1]; i++) cnt[i] = 0;
        for (int i = p; i < n; i++) work(vb[i]);

        int need = n / 2 - c0;
        for (int i = vb[n - 1]; i >= 1; i--) {
//        cout << i << " " << cnt[i] << endl;
            if (cnt[i] >= need) ans = max(ans, i);
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> va[i];
        solve();
    }

    return 0;
}