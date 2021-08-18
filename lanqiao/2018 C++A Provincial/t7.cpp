// 三体攻击

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e6 + 10;

int m;
int A, B, C;
int g[N];
int x1[N], y1[N], z1[N], x2[N], y2[N], z2[N], h[N];
int vd[N];

int getIdx(int x, int y, int z) {
    return (x * B + y) * C + z;
}

void insert(int i) {
    vd[getIdx(x1[i], y1[i], z1[i])] -= h[i];

    vd[getIdx(x2[i] + 1, y1[i], z1[i])] += h[i];
    vd[getIdx(x1[i], y2[i] + 1, z1[i])] += h[i];
    vd[getIdx(x1[i], y1[i], z2[i] + 1)] += h[i];

    vd[getIdx(x2[i] + 1, y2[i] + 1, z1[i])] -= h[i];
    vd[getIdx(x2[i] + 1, y1[i], z2[i] + 1)] -= h[i];
    vd[getIdx(x1[i], y2[i] + 1, z2[i] + 1)] -= h[i];

    vd[getIdx(x2[i] + 1, y2[i] + 1, z2[i] + 1)] += h[i];
}

bool check(int mid) {
    memset(vd, 0, sizeof vd);
    for (int i = 1; i <= mid; i++) insert(i);

    for (int x = 1; x <= A; x++) {
        for (int y = 1; y <= B; y++) {
            for (int z = 1; z <= C; z++) {
                vd[getIdx(x, y, z)] += vd[getIdx(x - 1, y, z)] + vd[getIdx(x, y - 1, z)] + vd[getIdx(x, y, z - 1)]
                        - vd[getIdx(x - 1, y - 1, z)] - vd[getIdx(x - 1, y, z - 1)] - vd[getIdx(x, y - 1, z - 1)]
                        + vd[getIdx(x - 1, y - 1, z - 1)];

                if (g[getIdx(x, y, z)] + vd[getIdx(x, y, z)] < 0) return true;
            }
        }
    }

    return false;
}

void solve() {
    int left = 0, right = m;
    while (left < right) {
        int mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }

    cout << right << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> A >> B >> C >> m;
    for (int x = 1; x <= A; x++) {
        for (int y = 1; y <= B; y++) {
            for (int z = 1; z <= C; z++) {
                scanf("%d", &g[getIdx(x, y, z)]);
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%d%d%d%d", &x1[i], &x2[i], &y1[i], &y2[i], &z1[i], &z2[i], &h[i]);
    }

    solve();

    return 0;
}