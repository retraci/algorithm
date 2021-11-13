#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 1e6 + 10;
const ll MOD = 1e9 + 7;

ll n;
ll f[N];

void solve() {
    for (int i = 4; i <= n; i++) f[i] = 1;
    for (int i = n - 1; i >= 4; i--) {
        for (int j = i - 1; j <= n; j += i - 1) {
            for (int k = j; k <= j + 2; k++) {
                if (k > i) f[i] = (f[i] + f[k]) % MOD;
            }
        }
    }

    f[3] = 1;
    for (int i = 4; i <= n; i++) f[3] = (f[3] + f[i]) % MOD;
    f[2] = 1;
    for (int i = 3; i <= n; i++) f[2] = (f[2] + f[i]) % MOD;

    ll sum = (f[2] * n) % MOD;
    cout << sum << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    solve();

    return 0;
}