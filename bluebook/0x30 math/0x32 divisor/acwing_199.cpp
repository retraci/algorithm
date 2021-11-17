#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

ll n, K;

void solve() {
    ll ans = n * K;
    ll left, right;
    for (left = 1; left <= n; left = right + 1) {
        ll tmp = K / left;
        if (tmp == 0) break;
        right = min(n, K / tmp);
        ans -= tmp * ((left + right) * (right - left + 1) / 2);
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K;
    solve();

    return 0;
}