#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 12;

int n, m;
int st[1 << N];
vector<int> state[1 << N];
ll f[N][1 << N];

void solve() {
    int lim = 1 << n;

    // 预处理 1: 判断列的所有情况是否合法
    for (int mask = 0; mask < lim; mask++) {
        int valid = 1, cnt = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                if (cnt & 1) {
                    valid = 0;
                    break;
                }
                cnt = 0;
            } else {
                cnt++;
            }
        }
        if (cnt & 1) valid = 0;
        st[mask] = valid;
    }

    // 预处理 2: 把所有可以递推的状态存好
    for (int mask = 0; mask < lim; mask++) state[mask].clear();
    for (int from = 0; from < lim; from++) {
        for (int to = 0; to < lim; to++) {
            if ((from & to) == 0 && st[from | to]) {
                state[from].push_back(to);
            }
        }
    }

    // dp
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int mask = 0; mask < lim; mask++) {
            for (auto vk : state[mask]) {
                f[i + 1][vk] += f[i][mask];
            }
        }
    }

    cout << f[m][0] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    while (cin >> n >> m, n || m) {
        solve();
    }

    return 0;
}