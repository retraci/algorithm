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

int g[11][11];
int ans;

int row[11], col[11], cell[11][11];
int mp[1 << 11];

inline int lowbit(int x) {
    return x & -x;
}

void init() {
    for (int i = 0; i < 9; i++) mp[1 << i] = i;
    for (int i = 0; i < 9; i++) row[i] = col[i] = (1 << 9) - 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) cell[i][j] = (1 << 9) - 1;
    }
}

int get(int x, int y) {
    return min({x, 8 - x, y, 8 - y}) + 6;
}

void dfs(int rem, int cur) {
    if (rem == 0) {
        ans = max(ans, cur);
        return;
    }

    int mi = 10, nx, ny;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (g[i][j] != 0) continue;

            int mask = row[i] & col[j] & cell[i / 3][j / 3];
            int cnt = __builtin_popcount(mask);
            if (mi > cnt) {
                mi = cnt;
                nx = i, ny = j;
            }
        }
    }

    int mask = row[nx] & col[ny] & cell[nx / 3][ny / 3];
    while (mask) {
        int x = mp[lowbit(mask)] + 1;

        g[nx][ny] = x;
        row[nx] -= lowbit(mask);
        col[ny] -= lowbit(mask);
        cell[nx / 3][ny / 3] -= lowbit(mask);
        dfs(rem - 1, cur + x * get(nx, ny));
        row[nx] += lowbit(mask);
        col[ny] += lowbit(mask);
        cell[nx / 3][ny / 3] += lowbit(mask);
        g[nx][ny] = 0;

        mask -= lowbit(mask);
    }
}

void solve() {
    init();

    int cnt = 0, cur = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (g[i][j] == 0) {
                cnt++;
            } else {
                cur += g[i][j] * get(i, j);
                row[i] -= 1 << g[i][j] - 1;
                col[j] -= 1 << g[i][j] - 1;
                cell[i / 3][j / 3] -= 1 << g[i][j] - 1;
            }
        }
    }

    ans = -1;
    dfs(cnt, cur);
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) cin >> g[i][j];
    }
    solve();

    return 0;
}