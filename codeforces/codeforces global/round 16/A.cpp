#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll n, s;

bool check(ll mid) {
    ll a = (n + 1) / 2 - 1, b = n - a - 1;
    ll sum = mid + b * mid;

//    cout << mid << " " << a << " " << b << " " << sum << endl;

    return sum <= s;
}

void solve() {
    ll left = 0, right = s;
    while (left < right) {
        ll mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> s;
        solve();
    }

    return 0;
}