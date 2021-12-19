#include<bits/stdc++.h>

#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define endl '\n'
using namespace std;
#define int long long
const int mod = 998244353;

int ask(int m) {
    if (m < 0) return 0;
    else return m;
}

int f[2][2][1000005], n, m, k;
int x1, y1, x2, y2;

signed main() {
    cin >> n >> m >> k;
    cin >> x1 >> x2 >> y1 >> y2;
    f[x1 != y1][x2 != y2][0] = 1;
    for (int i = 1; i < k; ++i) {
        f[1][1][i] = (ask(n - 1) * f[0][1][i - 1] % mod + ask(n - 2) * f[1][1][i - 1] % mod +
                ask(m - 1) * f[1][0][i - 1] % mod + ask(m - 2) * f[1][1][i - 1] % mod) % mod;
        f[1][0][i] = (ask(n - 2) * f[1][0][i - 1] % mod + f[1][1][i - 1] + ask(n - 1) * f[0][0][i - 1] % mod) % mod;
        f[0][1][i] = (ask(m - 2) * f[0][1][i - 1] % mod + f[1][1][i - 1] + ask(m - 1) * f[0][0][i - 1] % mod) % mod;
        f[0][0][i] = (f[0][1][i - 1] + f[1][0][i - 1]) % mod;
    }
    cout << (f[1][0][k - 1] + f[0][1][k - 1]) % mod;
}