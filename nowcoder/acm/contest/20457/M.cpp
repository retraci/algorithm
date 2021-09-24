#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int n, k;

void solve() {
    if (k >= n) cout << 2 << endl;
    else cout << (2 * n + k - 1) / k;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> k;
    solve();

    return 0;
}