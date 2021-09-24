#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 200000 + 10;

int n, K;
int va[N];

void solve() {
    sort(va, va + n);

    if (K == n - 1) {
        long long ans = 0;
        for (int i = 0; i < n; i++) ans += va[i];
        cout << ans << endl;
        return;
    }

    cout << va[(n - K + 1) / 2 - 1] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> K;
        for (int i = 0; i < n; i++) {
            cin >> va[i];
        }
        solve();
    }

    return 0;
}