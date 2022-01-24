#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll unsigned long long

ll K, x;

bool check(ll mid) {
    if (mid <= K) {
        if (mid & 1) {
            ll sum = (mid + 1) / 2 * mid;
            return sum < x;
        } else {
            ll sum = mid / 2 * (mid + 1);
            return sum < x;
        }
    }

    ll sum = 0;
    if (K & 1) {
        sum = (K + 1) / 2 * K;
    } else {
        sum = K / 2 * (K + 1);
    }

    ll s = K - 1, t = K - (mid - K);
    sum += (s + t) * (mid - K) / 2;

    return sum < x;
}

void solve() {
    ll tt = 0;
    if (K & 1) {
        tt = (K + 1) / 2 * K;
    } else {
        tt = K / 2 * (K + 1);
    }

    tt = (tt - K) * 2 + K;
    if (x >= tt) {
        cout << K * 2 - 1 << endl;
        return;
    }

//    check(4);

    ll left = 0, right = 2 * K;
    while (left < right) {
        ll mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left + 1 << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> K >> x;
        solve();
    }

    return 0;
}