#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110, M = 110;

int n, m;
int vv[N], vw[N], vs[N];
int f[M];

void solve() {
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 0; k <= vs[i]; k++) {
                if (j >= vv[i] * k) f[j] = max(f[j], f[j - vv[i] * k] + vw[i] * k);
            }
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