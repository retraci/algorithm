#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 310;

int n;
int va[N];
int f[N][N];
int s[N];

void solve() {
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + va[i];
    }

    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; i++) f[i][i] = 0;

    for (int len = 2; len <= n; len++) {
        for (int lt = 1; lt + len - 1 <= n; lt++) {
            int rt = lt + len - 1;
            for (int k = lt; k <= rt - 1; k++) {
                f[lt][rt] = min(f[lt][rt], f[lt][k] + f[k + 1][rt] + s[rt] - s[lt - 1]);
            }
        }
    }

    cout << f[1][n] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> va[i];
    }
    solve();

    return 0;
}