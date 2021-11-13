#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int n;

void solve() {
    int ans = 10;
    for (int i = 2; i <= n; i++) {
        ans += 2;
    }

    cout << ans << endl;
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