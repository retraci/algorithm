// 外卖店优先级

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 100010;

int n, m, T;
vector<int> shop[N];

void solve() {
    for (int i = 1; i <= n; i++) sort(shop[i].begin(), shop[i].end());

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int cur = 0;
        int t = 0;
        int flag = 0;
        for (int j = 0; j < shop[i].size(); j++) {
            // span - 1 步
            int none = max(0, shop[i][j] - t - 1);
            cur = max(0, cur - none);
            if (cur <= 3) flag = 0;

            // 最后一步
            cur += 2;
            if (cur > 5) flag = 1;

            t = shop[i][j];
        }

        cur -= T - t;
        if (cur <= 3) flag = 0;

        ans += flag;
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> m >> T;
    for (int i = 0, a, b; i < m; i++) {
        scanf("%d%d", &a, &b);
        shop[b].push_back(a);
    }
    solve();

    return 0;
}