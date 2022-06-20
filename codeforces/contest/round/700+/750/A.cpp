#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int a, b, c;

void solve() {
    if (c & 1) {
        if (b & 1) {
            if (a & 1) {
                cout << 0 << endl;
            } else {
                cout << 1 << endl;
            }
        } else {
            if (a & 1) {
                cout << 0 << endl;
            } else {
                cout << 1 << endl;
            }
        }
    } else {
        if (b & 1) {
            if (a & 1) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        } else {
            if (a & 1) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }

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