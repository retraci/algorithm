#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int a, b, c;
int mx, cnt;

void work(int x) {
    if (x == mx) {
        if (cnt == 1) cout << 0 << " ";
        else cout << 1 << " ";
    } else {
        cout << mx - x + 1 << " ";
    }
}

void solve() {
    mx = max({a, b, c});
    cnt = (a == mx) + (b == mx) + (c == mx);

    work(a);
    work(b);
    work(c);
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
        cin >> a >> b >> c;
        solve();
    }

    return 0;
}