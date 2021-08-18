#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1010, M = 2010;

int n, m;
int vv[N], vw[N], vs[N];
int va[15 * N], vb[15 * N], tt;
int f[M];

void solve() {
    for (int i = 1; i <= n; i++) {
        int k = 1;
        while (k <= vs[i]) {
            tt++;
            va[tt] = vv[i] * k;
            vb[tt] = vw[i] * k;
            vs[i] -= k;
            k *= 2;
        }

        if (vs[i]) {
            tt++;
            va[tt] = vv[i] * vs[i];
            vb[tt] = vw[i] * vs[i];
        }
    }

    memset(f, 0, sizeof f);
    for (int i = 1; i <= tt; i++) {
        for (int j = m; j >= va[i]; j--) {
            f[j] = max(f[j], f[j - va[i]] + vb[i]);
        }
    }

    cout << f[m] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> vv[i] >> vw[i] >> vs[i];
    }
    solve();

    return 0;
}