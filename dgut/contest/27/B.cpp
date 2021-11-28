#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll L, R, K;

void solve() {
    ll lim = floor(log(R) / log(K));
    ll cur = 1, cnt = 0, flag = 0;
    while (cnt++ <= lim) {
        if (cur >= L) {
            flag = 1;
            cout << cur << " ";
        }
        cur *= K;
    }
    if (!flag) cout << -1 << endl;
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> L >> R >> K;
    solve();

    return 0;
}