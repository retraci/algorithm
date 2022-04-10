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

const int N = 10000010;
const int MOD = 1e9 + 7;

int n;
int f[2][2][2];

void solve() {
    f[1][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                f[i + 1 & 1][j][k] = 0;
            }
        }

        f[i + 1 & 1][0][0] += f[i & 1][1][1];

        f[i + 1 & 1][0][0] += f[i & 1][0][0];
        f[i + 1 & 1][1][0] += f[i & 1][0][1];
        f[i + 1 & 1][0][1] += f[i & 1][1][0];
        f[i + 1 & 1][1][1] += f[i & 1][0][0];

        f[i + 1 & 1][1][1] += f[i & 1][0][1];
        f[i + 1 & 1][1][1] += f[i & 1][1][0];
        f[i + 1 & 1][0][1] += f[i & 1][0][0];
        f[i + 1 & 1][1][0] += f[i & 1][0][0];

        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                if (f[i + 1 & 1][j][k] >= MOD) f[i + 1 & 1][j][k] %= MOD;
            }
        }
    }

    cout << f[n + 1 & 1][0][0];
}

int main() {
//    freopen("../in.txt", "r", stdin);
//    freopen("../out.txt", "w", stdout);

    cin >> n;
    solve();

    return 0;
}
