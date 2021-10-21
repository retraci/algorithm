#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 22;

int n, m, K;
string ss[N];

void work(int r, int c) {
    string tmp[N];
    for (int i = 0; i < n; i++) {
        tmp[i] = ss[i];
    }

    int len;
    for (len = 0; ; len++) {
        int x = r - len, y1 = c - len, y2 = c + len;

        if (x < 0 || y1 < 0 || y2 >= m) break;
        if (tmp[x][y1] == '.' || tmp[x][y2] == '.') break;

//        cout << len << endl;
//        cout << x << " " << y1 << " " << tmp[x][y1] << endl;
//        cout << x << " " << y2 << " " << tmp[x][y2] << endl;

        tmp[x][y1] = '#'; tmp[x][y2] = '#';
    }

    len--;
    if (len >= K) {
        for (int i = 0; i < n; i++) {
            ss[i] = tmp[i];
        }
    }
}

void solve() {
    for (int i = n - 1; i >= K; i--) {
        for (int j = 0; j < m; j++) {
            if (ss[i][j] == '.') continue;

            work(i, j);

//            for (int k = 0; k < n; k++) {
//                cout << ss[k] << endl;
//            }
//            cout << endl;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ss[i][j] == '*') {
                cout << "NO" << endl;
                return;
            }
        }
    }

    cout << "YES" << endl;
    return;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> K;
        for (int i = 0; i < n; i++) cin >> ss[i];
        solve();
    }

    return 0;
}