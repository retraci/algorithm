#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>

using namespace std;

const int N = 510;

int n;
int va[N][N];
bitset<2 * N> mat[N];

void print() {
    for (int i = 1; i <= n; i++) {
        cout << mat[i] << endl;
    }
}

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mat[j][i] = va[i][j];
        }
    }
    for (int j = 1; j <= n; j++) mat[j][n + j] = 1;
}

int gauss(int n, int m) {
    for (int i = 1; i <= m; i++) {
        int cur = i;
        while (cur <= n && !mat[cur].test(i)) cur++;
        if (cur > n) return -1;
        if (cur != i) swap(mat[cur], mat[i]);
        for (int j = 1; j <= n; j++) {
            if (i != j && mat[j].test(i)) mat[j] ^= mat[i];
        }
    }

    return 0;
}

void solve() {
    init();

    int res = gauss(n, n);
    if (res == -1) {
        cout << -1 << endl;
        return;
    }

    for (int k = 1; k <= n; k++) {
        int j = n + k;
        for (int i = 1; i <= n; i++) {
            if (mat[i].test(j)) cout << i << " ";
        }
        cout << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> va[i][j];
        }
    }
    solve();

    return 0;
}
