#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 3e5 + 10;

ll n, w;
ll va[N], vb[N];
int idx[N];

void solve() {
    for (int i = 1; i <= n; i++) idx[i] = i;
    sort(idx + 1, idx + n + 1, [&](auto &a, auto &b) {
        return va[a] > va[b];
    });

    ll ans = 0, x = 1;
    while (w && x <= n) {
        int id = idx[x];
        ll tmp = min(w, vb[id]);

        ans += tmp * va[id];

        vb[id] -= tmp;
        w -= tmp;
        if (vb[id] == 0) x++;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> w;
    for (int i = 1; i <= n; i++) cin >> va[i] >> vb[i];
    solve();

    return 0;
}