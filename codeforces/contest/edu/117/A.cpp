#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int xb, yb;

void solve() {
    for (int a = 0; a <= 50; a++) {
        for (int b = 0; b <= 50; b++) {
            if (a + b == abs(a - xb) + abs(b - yb)) {
                cout << a << " " << b << endl;
                return;
            }
        }
    }

    cout << -1 << " " << -1 << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> xb >> yb;
        solve();
    }

    return 0;
}