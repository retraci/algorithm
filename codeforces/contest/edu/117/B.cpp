#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n, a, b;

void solve() {
    int has1 = n - a, has2 = b - 1;
    if (a < b) has1--, has2--;

    int need = n / 2 - 1;
    if (need > has1 || need > has2) {
        cout << -1 << endl;
        return;
    }

    int id = n;
    cout << a << " ";
    for (int cnt = 0; cnt < need; id--) {
        if (id == a || id == b) continue;
        cout << id << " ";
        cnt++;
    }
    cout << b << " ";
    for (int cnt = 0; cnt < need; id--) {
        if (id == a || id == b) continue;
        cout << id << " ";
        cnt++;
    }
    cout << endl;
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
        cin >> n >> a >> b;
        solve();
    }

    return 0;
}