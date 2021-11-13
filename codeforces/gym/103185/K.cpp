#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

typedef pair<int, int> pii;

const int N = 1e4 + 10, M = 750 + 10;
const ll MOD = 1e9 + 7;

ll n, K, m;
ll mat[M][M], va[N];
pii vb[N][M];
ll f[N][M];

void init() {
    for (int k = 1; k <= n - 1; k++) {
        ll L = va[k] - m, R = va[k] + m;
        for (int i = 1; i <= K; i++) {
            int lb = lower_bound(mat[i] + 1, mat[i] + K + 1, L) - mat[i];
            int rb = upper_bound(mat[i] + 1, mat[i] + K + 1, R) - mat[i] - 1;
            vb[k][i] = {lb, rb};
        }
    }
}

void solve() {
    init();

    memset(f, 0, sizeof f);
    for (int i = 1; i <= K; i++) f[n][i] = f[n][i - 1] + 1;
    for (int k = n - 1; k >= 1; k--) {
        for (int i = 1; i <= K; i++) {
            auto &[L, R] = vb[k][i];
            f[k][i] = (f[k][i] + f[k + 1][R] - f[k + 1][L - 1] + MOD) % MOD;
        }
        for (int i = 1; i <= K; i++) {
            f[k][i] = (f[k][i] + f[k][i - 1]) % MOD;
        }
    }

    cout << f[1][K] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> K >> m;
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= K; j++) {
            cin >> mat[i][j];
        }
    }
    cin >> n;
    for (int k = 1; k <= n - 1; k++) {
        cin >> va[k];
    }
    solve();

    return 0;
}