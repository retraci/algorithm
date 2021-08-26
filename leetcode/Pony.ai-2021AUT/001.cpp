#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110;
const int BASE = 100;
const int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};

int n, q;
int mp[N * 2][N * 2];
int s[N * 2][N * 2];

void solve() {
    mp[0 + BASE][0 + BASE] = n;
    int flag = 1;
    while (flag) {
        flag = 0;
        for (int x = -99; x <= 99; x++) {
            for (int y = -99; y <= 99; y++) {
                if (mp[x + BASE][y + BASE] >= 8) {
                    flag = 1;
                    for (int k = 0; k < 8; k++) {
                        int nx = x + dx[k];
                        int ny = y + dy[k];
                        mp[nx + BASE][ny + BASE] += mp[x + BASE][y + BASE] / 8;
                    }
                    mp[x + BASE][y + BASE] %= 8;
                }
            }
        }
    }

    memset(s, 0, sizeof s);
    for (int i = -99; i <= 99; i++) {
        for (int j = -99; j <= 99; j++) {
            s[i + BASE][j + BASE] = s[i - 1 + BASE][j + BASE] + s[i + BASE][j - 1 + BASE] - s[i - 1 + BASE][j - 1 + BASE] + mp[i + BASE][j + BASE];
        }
    }

    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 = max(x1, -99) + BASE;
        y1 = max(y1, -99) + BASE;
        x2 = min(x2, 99) + BASE;
        y2 = min(y2, 99) + BASE;

        if (x1 > x2 || y1 > y2) {
            cout << 0 << endl;
        } else {
            cout << s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1] << endl;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> q;
    solve();

    return 0;
}