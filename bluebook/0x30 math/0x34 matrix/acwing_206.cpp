#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 110;

struct Mat {
    int r, c;
    ll s[N][N];
    Mat() { memset(s, 0, sizeof s); }
    Mat(int _r, int _c):r(_r), c(_c) { memset(s, 0, sizeof s); }
};

int n, m, t, act;
string a[11];
string b[11];
int c[N][N];

int p;
Mat e[65];
Mat f, d;

Mat multi(Mat& a, Mat& b) {
    Mat res(a.r, b.c);
    for (int i = 1; i <= a.r; i++) {
        for (int j = 1; j <= b.c; j++) {
            for (int k = 1; k <= a.c; k++) {
                res.s[i][j] += a.s[i][k] * b.s[k][j];
            }
        }
    }
    return res;
}

Mat qpow(Mat a, ll b) {
    Mat res = a;
    b--;
    while (b) {
        if (b & 1) res = multi(res, a);
        a = multi(a, a);
        b >>= 1;
    }
    return res;
}

int getIdx(int r, int c) { return (r - 1) * m + c; }

void init() {
    p = getIdx(n + 1, 1);

    for (int k = 1; k <= 60; k++) {
        e[k].r = e[k].c = p;
        e[k].s[p][p] = 1;

        // 无视 D操作, 只有 数字操作 才会保留当前格子的数字, 其他操作均把当前格子的数字消除
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int x = a[i - 1][j - 1] - '0', y = c[i][j];

                if (b[x][y] >= '0' && b[x][y] <= '9') {
                    e[k].s[p][getIdx(i, j)] = b[x][y] - '0';
                    e[k].s[getIdx(i, j)][getIdx(i, j)] = 1;
                }
                if (b[x][y] == 'N' && i - 1 >= 1) {
                    e[k].s[getIdx(i, j)][getIdx(i - 1, j)] = 1;
                }
                if (b[x][y] == 'W' && j - 1 >= 1) {
                    e[k].s[getIdx(i, j)][getIdx(i, j - 1)] = 1;
                }
                if (b[x][y] == 'S' && i + 1 <= n) {
                    e[k].s[getIdx(i, j)][getIdx(i + 1, j)] = 1;
                }
                if (b[x][y] == 'E' && j + 1 <= m) {
                    e[k].s[getIdx(i, j)][getIdx(i, j + 1)] = 1;
                }

                c[i][j] = (y + 1) % b[x].size();
            }
        }
    }

    d = e[1];
    for (int k = 2; k <= 60; k++) {
        d = multi(d, e[k]);
    }
    f.r = 1; f.c = p;
    f.s[1][p] = 1;
}

void solve() {
    init();

    int u = t / 60, v = t % 60;
    if (u >= 1) {
        d = qpow(d, u);
        f = multi(f, d);
    }
    for (int k = 1; k <= v; k++) f = multi(f, e[k]);

    ll ans = 0;
    for (int i = 1; i < p; i++) ans = max(ans, f.s[1][i]);

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> m >> t >> act;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < act; i++) cin >> b[i];
    solve();

    return 0;
}