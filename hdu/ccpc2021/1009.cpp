#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

int n;
string str;
ll a[N];

void solve() {
    for (int i = 1; i <= n; i++) {
        if (str[i - 1] == 'L') a[i] = -1;
        else if (str[i - 1] == 'R') a[i] = 1;
        else if (str[i - 1] == 'U') a[i] = -1e6;
        else if (str[i - 1] == 'D') a[i] = 1e6;
    }

    for (int i = 1; i <= n; i++) {
        a[i] += a[i - 1];
    }

    ll ans = 0;
    unordered_map<ll, ll> mp;
    for (int i = 0; i <= n; i++) {
        ll s = a[i];
        ans += mp[s];
        mp[a[i]]++;
    }

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
        cin >> n;
        cin >> str;
        solve();
    }

    return 0;
}