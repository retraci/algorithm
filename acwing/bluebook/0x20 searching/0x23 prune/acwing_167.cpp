#include <bits/stdc++.h>

using namespace std;

const int N = 70;

int n;
int va[N];
int vis[N];

bool dfs(int x, int curLen, int curCnt, int len, int cnt) {
    if (curCnt >= cnt) return true;

    // 凑齐一段 就从 0 开始搜
    if (curLen == len) return dfs(0, 0, curCnt + 1, len, cnt);

    int fail = 0;
    for (int i = x; i < n; i++) {
        if (fail != va[i] && !vis[i] && curLen + va[i] <= len) {
            vis[i] = 1;
            // 每次搜更小的
            if (dfs(i + 1, curLen + va[i], curCnt, len, cnt)) return true;
            vis[i] = 0;

            fail = va[i];
            // 等效剪枝
            // 1. 第一条都失败，那分支就失败
            // 2. 凑齐了一条，再重新开始凑失败了，那分支就失败
            if (curLen == 0 || curLen + va[i] == len) return false;
        }
    }

    return false;
}

void solve() {
    memset(vis, 0, sizeof vis);
    sort(va, va + n, greater<int>());

    int sum = 0;
    for (int i = 0; i < n; i++) sum += va[i];

    for (int len = va[0]; len <= sum; len++) {
        if (sum % len != 0) continue;
        int cnt = sum / len;
        if (dfs(0, 0, 0, len, cnt)) {
            cout << len << endl;
            break;
        }
    }
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    while (cin >> n && n) {
        for (int i = 0; i < n; i++) cin >> va[i];
        solve();
    }

    return 0;
}