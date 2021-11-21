#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

int n, ca;
ll va[N];
ll need[N];

bool check(ll mid) {
    for (int i = 1; i <= n; i++) need[i] = max(0LL, mid - va[i]);

    ll s1 = 0;
    for (int i = 1; i <= n; i++) s1 += need[i];
    if (s1 > mid) return false;

    for (int i = 1; i <= n; i++) {
        if (va[i] < s1 - need[i]) return false;
    }

    return true;
}

void solve() {
//    check(4);

    ll left = 0, right = 1e14;
    while (left < right) {
        ll mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }
    cout << "Case #" + to_string(++ca) + ": " << left + 1 << endl;
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}