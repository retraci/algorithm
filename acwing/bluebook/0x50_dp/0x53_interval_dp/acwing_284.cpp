#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 310;
const ll MOD = 1e9;

string str;
ll f[N][N];

void solve() {
    int n = str.size();
    if ((n & 1) == 0) {
        cout << 0 << endl;
        return;
    }

    memset(f, 0, sizeof f);

    for (int len = 1; len <= n; len += 2) {
        for (int L = 0; L + len - 1 < n; L++) {
            int R = L + len - 1;
            if (str[L] != str[R]) continue;

            if (len == 1) {
                f[L][R] = 1;
                continue;
            }

            for (int k = L + 1; k < R; k++) {
                if (str[k] != str[R - 1]) continue;

                f[L][R] = (f[L][R] + f[L][k - 1] * f[k][R - 1] % MOD) % MOD;
            }
        }
    }

    cout << f[0][n - 1] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> str;
    solve();

    return 0;
}