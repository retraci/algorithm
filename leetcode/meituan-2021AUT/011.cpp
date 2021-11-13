#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll d;
ll v[3];
ll w[3];

bool cmp(int x, int y) {
    return w[x] < w[y];
}

void solve() {
    ll va[3] = {0, 1, 2};
    sort(va, va + 3, cmp);

    int p = 2;
    ll ans = 0;
    while (d > 0 && p >= 0) {
        int cur = va[p];

        ll cnt = v[cur];
        ll price = w[cur];

        cnt = min(cnt, d);
        ans += cnt * price;

        v[cur] -= cnt;
        d -= cnt;
        if (v[cur] <= 0) p--;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> v[0] >> v[1] >> v[2] >> d >> w[0] >> w[1] >> w[2];
    solve();

    return 0;
}