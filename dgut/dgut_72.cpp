#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll L, R;

bool check(ll x) {
    return x % 3 == 1 && x % 5 == 3;
}

void solve() {
    ll ans = 0;
    for (ll i = L; i <= R; i++) {
        if (check(i)) ans += i;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> L >> R;
    solve();

    return 0;
}