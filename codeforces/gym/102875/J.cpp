#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iomanip>

using namespace std;

const int N = 1e6 + 10;

int n;
int f[N];

int dfs(int x) {
    if (f[x]) return f[x];
    int res = dfs(n % x);
    return res + 1;
}

int solve() {
    for (int i = 0; i <= n; i++) f[i] = 0;
    f[0] = f[1] = 1;
    for (int i = 1; i <= n - 1; i++) f[i] = dfs(i);
    double ans = 0;
    for (int i = 1; i <= n - 1; i++) ans += f[i];
    cout << fixed << setprecision(10);
    cout << ans / (n - 1) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        solve();
    }

    return 0;
}