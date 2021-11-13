#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 1e6 + 10;

ll n, d;
ll va[N];

ll calc(ll d) {
    ll sum = 0, mx = 0, mi = 0;
    ll a1 = va[1];
    for (int i = 2; i <= n; i++) {
        ll a2 = va[i];
        sum += d - a2 + a1;
        mx = max(mx, sum);
        mi = min(mi, sum);
        a1 = a2;
    }

    return mx - mi;
}

void solve() {
    ll ans = min(calc(d), calc(-d));
    if (ans & 1) {
        cout << (ans >> 1) << ".5" << endl;
    } else {
        cout << (ans >> 1) << ".0" << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> d;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}