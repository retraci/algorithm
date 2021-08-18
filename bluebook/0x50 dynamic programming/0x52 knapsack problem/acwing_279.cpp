#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const ll MOD = 2147483648;
const int N = 4010;

int n;
ll f[N];

void solve() {
    f[0] = 1;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i; j <= n; j++) {
            f[j] = (f[j] + f[j - i]) % MOD;
        }
    }

    cout << f[n] << endl;
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