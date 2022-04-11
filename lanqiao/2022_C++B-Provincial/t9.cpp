#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>

using namespace std;

#define ll long long

const ll MOD = 1000000007;

int n, m;
ll f[210][110][110];
ll ans;
string path;

void work2() {
    f[0][2][0] = 1;

    for (int i = 0; i < n + m; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= i; k++) {
                if (j * 2 <= m) {
                    f[i + 1][j * 2][k] += f[i][j][k];
                    if (f[i + 1][j * 2][k] >= MOD) f[i + 1][j * 2][k] -= MOD;
                }
                if (k + 1 <= m) {
                    f[i + 1][j - 1][k + 1] += f[i][j][k];
                    if (f[i + 1][j - 1][k + 1] >= MOD) f[i + 1][j - 1][k + 1] -= MOD;
                }
            }
        }
    }

    ans = f[n + m - 1][1][m - 1];
}

void dfs(int u, int c1, int c2) {
    if (c1 == 0 && c2 == 0) {
        if (u == 0 && path.back() == '0') ans++;
        if (ans >= MOD) ans -= MOD;
        return;
    }

    if (u > c2) return;

    if (c2 > 0 && u > 0) {
        path.push_back('0');
        dfs(u - 1, c1, c2 - 1);
        path.pop_back();
    }
    if (c1 > 0) {
        path.push_back('1');
        dfs(u * 2, c1 - 1, c2);
        path.pop_back();
    }
}

void solve() {
    if (n <= 10 && m <= 10) dfs(2, n, m);
    else work2();

    cout << ans;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    solve();

    return 0;
}
