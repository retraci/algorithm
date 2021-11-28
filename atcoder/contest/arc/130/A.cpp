#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int n;
string str;

void solve() {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && str[j] == str[i]) j++;
        ll len = j - i;

        if (len >= 2) {
            ans += len * (len - 1) / 2;
        }

        i = j - 1;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> str;
    solve();

    return 0;
}