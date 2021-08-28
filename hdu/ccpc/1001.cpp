#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll n;
ll ans;

bool check1(ll mid) {
    ll x = 2 * mid + 1;
    return 3 * x + 1 >= n + 1;
}

bool check2(ll mid) {
    ll x = 2 * mid;
    return x / 2 <= n;
}

void solve() {
    ans = 0;
    ll left = 0, right = 2e9;
    while (left < right) {
        ll mid = left + right >> 1;
        if (check1(mid)) right = mid;
        else left = mid + 1;
    }
    ll num1 = 2 * left + 1;

    left = 1, right = 2e9;
    while (left < right) {
        ll mid = left + right + 1 >> 1;
        if (check2(mid)) left = mid;
        else right = mid - 1;
    }
    ll num2 = 2 * left;

    ans += (n - num1) / 2 + 1;
    ans += (num2 - n - 1) / 2 + 1;

//    cout << num1 << " " << num2 << endl;
//    cout << (n - num1) / 2 + 1 << " " << (num2 - n - 1) / 2 + 1 << endl;

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
        scanf("%lld", &n);
        solve();
    }

    return 0;
}