#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

int n;
int va[N];

void solve() {
    if (n & 1) {
        if (va[1] + va[2] != 0) cout << -va[3] << " " << -va[3] << " " << va[1] + va[2] << " ";
        else if (va[1] + va[3] != 0) cout << -va[2] << " " << va[1] + va[3] << " " << -va[2] << " ";
        else if (va[2] + va[3] != 0) cout << va[2] + va[3] << " " << -va[1] << " " << -va[1] << " ";
        for (int i = 4; i <= n; i += 2) {
            cout << va[i + 1] << " " << -va[i] << " ";
        }
    } else {
        for (int i = 1; i <= n; i += 2) {
            cout << va[i + 1] << " " << -va[i] << " ";
        }
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}