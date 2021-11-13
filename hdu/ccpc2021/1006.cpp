#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T, n;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n;
        if (n % 4 == 0) {
            cout << n << endl;
            for (int i = 1; i <= n; i += 4)
                cout << "1001";
            cout << endl;
        } else if (n % 4 == 1) {
            cout << n << endl;
            cout << "1";
            for (int i = 2; i <= n; i += 4)
                cout << "1001";
            cout << endl;
        } else if (n % 4 == 3) {
            cout << n - 1 << endl;
            cout << "01";
            for (int i = 4; i <= n; i += 4)
                cout << "1001";
            cout << endl;
        } else if (n % 4 == 2) {
            cout << n + 2 << endl;
            cout << "0001";
            for (int i = 3; i <= n; i += 4)
                cout << "1001";
            cout << endl;
        }
    }

    return 0;
}
