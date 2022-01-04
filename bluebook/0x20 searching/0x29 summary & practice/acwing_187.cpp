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
typedef tuple<int, int, int> ti3;
typedef tuple<ll, ll, ll> tl3;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 55;

int n;
int va[N];

int up[N], down[N];
int ans;

void dfs(int cur, int su, int sd) {
    if (su + sd >= ans) return;
    if (cur > n) {
        ans = min(ans, su + sd);
        return;
    }

    // 贪心找最大的
    {
        int tmp = 0, id = 0;
        for (int i = 1; i <= su; i++) {
            if (up[i] >= va[cur]) continue;

            if (up[i] > tmp) {
                tmp = up[i], id = i;
            }
        }

        if (id != 0) {
            up[id] = va[cur];
            dfs(cur + 1, su, sd);
            up[id] = tmp;
        } else {
            // 自己开一个上升序列
            up[su + 1] = va[cur];
            dfs(cur + 1, su + 1, sd);
        }
    }

    // 贪心找最小的
    {
        int tmp = 1e9, id = 0;
        for (int i = 1; i <= sd; i++) {
            if (down[i] <= va[cur]) continue;

            if (down[i] < tmp) {
                tmp = down[i], id = i;
            }
        }

        if (id != 0) {
            down[id] = va[cur];
            dfs(cur + 1, su, sd);
            down[id] = tmp;
        } else {
            // 自己开一个下降序列
            down[sd + 1] = va[cur];
            dfs(cur + 1, su, sd + 1);
        }
    }
}

void solve() {
    ans = 1e9;
    dfs(1, 0, 0);
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}