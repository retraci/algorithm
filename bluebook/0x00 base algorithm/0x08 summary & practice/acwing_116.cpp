#include <bits/stdc++.h>

using namespace std;

char g[5][5];
int cnt[5][5];
int n;
int ans[5][5];

void solve() {
    n = 17;
    int lim = 1 << 16;
    for (int s = 0; s < lim; s++) {
        int tmp[5][5] = {0};

        int count = 0;
        memset(cnt, 0, sizeof(cnt));
        for (int k = 0; k < 16; k++) {
            if (s >> k & 1) {
                int x = k / 4, y = k % 4;
                tmp[x][y] = 1;
                count++;

                for (int i = 0; i < 4; i++) cnt[i][y]++;
                for (int j = 0; j < 4; j++) cnt[x][j]++;
                cnt[x][y]--;
            }
        }

        int flag = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (g[i][j] == '+' && !(cnt[i][j] & 1)) flag = 1;
                if (g[i][j] == '-' && (cnt[i][j] & 1)) flag = 1;
            }
        }

        if (!flag) {
            if (n > count) {
                n = count;
                memcpy(ans, tmp, sizeof(ans));
            }
        }
    }

    cout << n << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (ans[i][j]) cout << i+1 << " " << j+1 << endl;
        }
    }
}

int main() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> g[i][j];
        }
    }
    solve();

    return 0;
}