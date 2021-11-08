#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;

#define ll long long

const int N = 1010;
const ll MOD = 1e9 + 7;

ll n;
ll f[N][N];

void solve() {
    f[0][0] = 1;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= n / 2; j++) {
            f[i][j] = (f[i][j] + f[i - 1][j]) % MOD;
            f[i][j] = (f[i][j] + f[i - 1][j - 1]) % MOD;
        }
    }

    cout << 2 * f[n - 1][n / 2] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    solve();

    return 0;
}