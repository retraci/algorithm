#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const ll MOD = 10000;

struct Mat {
    ll s[5][5];
    int r, c;
    Mat() { memset(s, 0, sizeof s); }
};

int n;
Mat a, f;

void init() {
    a.r = a.c = 2;
    a.s[1][1] = 1; a.s[1][2] = 1;
    a.s[2][1] = 1; a.s[2][2] = 0;

    f.r = 2; f.c = 1;
    f.s[1][1] = 1;
    f.s[2][1] = 0;
}

Mat multi(Mat &a, Mat &b) {
    Mat res; res.r = a.r; res.c = b.c;
    for (int i = 1; i <= res.r; i++) {
        for (int j = 1; j <= res.c; j++) {
            for (int k = 1; k <= a.c; k++) {
                res.s[i][j] = (res.s[i][j] + (a.s[i][k] * b.s[k][j] % MOD)) % MOD;
            }
        }
    }

    return res;
}

Mat qpow(Mat a, int b) {
    Mat res = a;
    b--;

    while (b) {
        if (b & 1) res = multi(res, a);
        a = multi(a, a);
        b >>= 1;
    }

    return res;
}

void solve() {
    if (n == 0) { cout << 0 << endl; return; }
    if (n == 1) { cout << 1 << endl; return; }

    init();
    a = qpow(a, n - 1);
    f = multi(a, f);

    cout << f.s[1][1] << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    while (cin >> n, n != -1) {
        solve();
    }

    return 0;
}