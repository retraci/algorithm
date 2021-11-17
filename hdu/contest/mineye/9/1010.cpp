#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

ll n, s, t, h;
ll va[N], vb[N];

void solve() {
    va[0] = vb[0] = 1, va[n] = vb[n] = h;
    sort(va + 1, va + 1 + n - 1);
    sort(vb + 1, vb + 1 + n - 1);

    ll mx1 = va[n - s], mx2 = vb[n - s];
    ll mi1 = va[0 + t], mi2 = vb[0 + t];
    ll s1 = 0, s2 = 0;
    for (int i = t + 1; i < n - s; i++) {
        s1 += va[i];
        s2 += vb[i];
    }

    ll L1 = s1 + mi1, R1 = s1 + mx1;
    ll L2 = s2 + mi2, R2 = s2 + mx2;
    if (R1 <= L2) {
        puts("IMPOSSIBLE");
        return;
    }
    if (L1 > R2) {
        printf("%lld\n", 1 - h);
        return;
    }

    ll need = s2 - s1 + 1;
    ll d = 0;
    if (L1 > L2) d = max(d, mi1 - 1);
    if (R1 > R2) d = max(d, h - mx2);

    printf("%lld\n", need - d);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) {
        scanf("%lld%lld%lld%lld", &n, &s, &t, &h);
        for (int i = 1; i <= n - 1; i++) {
            scanf("%lld", &va[i]);
        }
        for (int i = 1; i <= n - 1; i++) {
            scanf("%lld", &vb[i]);
        }

        solve();
    }

    return 0;
}