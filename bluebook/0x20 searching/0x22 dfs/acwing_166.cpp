#include <bits/stdc++.h>

using namespace std;

string str;
char va[9][9];
int sx[9], sy[9], sc[3][3];
int mp1[1 << 9], mp2[1 << 9];

int lowbit(int x) {
    return x & (-x);
}

int getStatus(int x, int y) {
    return sx[x] & sy[y] & sc[x / 3][y / 3];
}

bool dfs(int cnt) {
    if (cnt == 0) return true;

    // 选择分支数最小的进行 dfs
    int mi = 10;
    int x, y;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (va[i][j] != '.') continue;

            int s = getStatus(i, j);
            // 避免循环，mp1 为预处理每种可能的 '.' 数
            int c = mp1[s];
            if (mi > c) mi = c, x = i, y = j;
        }
    }

    int s = getStatus(x, y);
    for (int i = s; i; i -= lowbit(i)) {
        int tmp = lowbit(i);
        // 避免循环， 预处理 mp2 来快速获取当前 lowbit 所代表的数字
        int cur = mp2[tmp];

//        cout << x << " " << y << " " << cur << endl;

        va[x][y] = cur + '0';
        sx[x] -= 1 << cur;
        sy[y] -= 1 << cur;
        sc[x / 3][y / 3] -= 1 << cur;
        if (dfs(cnt - 1)) return true;
        va[x][y] = '.';
        sx[x] += 1 << cur;
        sy[y] += 1 << cur;
        sc[x / 3][y / 3] += 1 << cur;
    }

    return false;
}

void solve() {
    // 初始化状态
    for (int i = 0; i < 9; i++) sx[i] = (1 << 9) - 1;
    for (int j = 0; j < 9; j++) sy[j] = (1 << 9) - 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sc[i][j] = (1 << 9) - 1;
        }
    }

    // 预处理 mp1
    int lim = 1 << 9;
    for (int s = 0; s < lim; s++) {
        int tmp = 0;
        for (int i = s; i; i -= lowbit(i)) {
            tmp++;
        }
        mp1[s] = tmp;
    }

    // 预处理 mp2
    for (int i = 0; i < 9; i++) mp2[1 << i] = i;

    // 转为表格，维护状态
    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            va[i][j] = str[i * 9 + j];
            if (va[i][j] != '.') {
                // 数字 [1-9] 转 [0-8]
                va[i][j]--;

                int num = va[i][j] - '0';
                sx[i] -= 1 << num;
                sy[j] -= 1 << num;
                sc[i / 3][j / 3] -= 1 << num;
            } else {
                cnt++;
            }
        }
    }

    dfs(cnt);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            va[i][j]++;
            cout << va[i][j];
        }
    }
    cout << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    while (cin >> str && str[0] != 'e') {
        solve();
    }

    return 0;
}