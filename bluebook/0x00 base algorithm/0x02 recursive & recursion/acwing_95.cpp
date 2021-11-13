#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n = 5;
char va[11][11], flip[11][11];

void solve() {
    int lim = 1 << 5;

    int ans = 25;
    for (int s = 0; s < lim; s++) {
        int cnt = 0;
        memset(flip, 0, sizeof(flip));
        for (int bit = 0; bit < n; bit++) {
            if (s >> bit & 1) {
                cnt++;
                flip[1][bit+1] = 1;
            }
        }

        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int count = va[i-1][j] + flip[i-1][j] + flip[i-1][j-1] + flip[i-1][j+1] + flip[i-2][j];
                if (count & 1) continue;
                flip[i][j] = 1;
                cnt++;
            }
        }

        int flag = 0;
        for (int j = 1; j <= n; j++) {
            int count = va[n][j] + flip[n][j] + flip[n][j-1] + flip[n][j+1] + flip[n-1][j];
            if (count & 1) continue;
            flag = 1;
            break;
        }

        if (!flag) ans = min(ans, cnt);
    }

    if (ans <= 6) cout << ans << endl;
    else cout << -1 << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> va[i][j];
                va[i][j] -= '0';
            }
        }

        solve();
    }

    return 0;
}

