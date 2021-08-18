// 剪邮票

#include <bits/stdc++.h>
#pragma GCC optimize(2)

using namespace std;

const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int n, m;
int ans;
int fa[20];

bool vaild(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int getNum(int x, int y) {
    return x * m + y;
}

void solve() {
    n = 3, m = 4;

    int lim = 1 << 12;
    for (int s = 0; s < lim; s++) {
        int va[20], cnt = 0;
        for (int i = 0; i < 12; i++) {
            if (s >> i & 1) va[cnt++] = i;
        }
        if (cnt != 5) continue;

        int xs[5], ys[5];
        for (int i = 0; i < 5; i++) {
            xs[i] = va[i] / m;
            ys[i] = va[i] % m;
        }

        for (int i = 0; i < 15; i++) fa[i] = i;

        for (int i = 0; i < 5; i++) {
            int x = xs[i], y = ys[i];
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                if (!vaild(nx, ny)) continue;

                int num = getNum(nx, ny);
                for (int j = 0; j < 5; j++) {
                    if (va[j] == num) {
                        int xx = va[i];
                        int yy = va[j];

                        int tx = find(xx);
                        int ty = find(yy);
                        fa[tx] = ty;

                        break;
                    }
                }
            }
        }

        int sum = 0;
        for (int i = 0; i < 5; i++) {
            int x = va[i];
            sum += x == fa[x];
        }
        if (sum == 1) ans++;
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();

    return 0;
}