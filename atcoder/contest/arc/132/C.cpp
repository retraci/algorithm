#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const ll MOD = 998244353;

const int N = 510;

int n, d;
int va[N];

ll f[N][2020];

void solve() {
    int m = 2 * d + 1;
    int lim = 1 << m;
    f[0][(1 << d + 1) - 1] = 1;
    for (int i = 0; i < n; i++) {
        for (int mask = 1; mask < lim; mask += 2) {
            int bak = mask >> 1;

            for (int j = 0; j < m; j++) {
                if (bak >> j & 1) continue;
                if (va[i + 1] != -1 && j - d != va[i + 1] - (i + 1)) continue;

                int ns = bak | 1 << j;
                f[i + 1][ns] = (f[i + 1][ns] + f[i][mask]) % MOD;
            }
        }
    }

    cout << f[n][(1 << d + 1) - 1] << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> d;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}