#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2010;

struct Node {
    int sum, id1, id2;

    bool operator<(const Node &that) const {
        return sum > that.sum;
    }
};

int n, m;
int va[N][N];
int ans[N];
int tmp[N];

void merge(int r) {
    priority_queue<Node> que;
    for (int i = 1; i <= m; i++) {
        que.push({ans[1] + va[r][i], 1, i});
    }

    for (int i = 1; i <= m; i++) {
        auto [cur, id1, id2] = que.top(); que.pop();
        tmp[i] = cur;
        que.push({ans[id1 + 1] + va[r][id2], id1 + 1, id2});
    }

    memcpy(ans, tmp, sizeof tmp);
}

void solve() {
    memcpy(ans, va[1], sizeof va[1]);
    sort(ans + 1, ans + m + 1);

    for (int i = 2; i <= n; i++) merge(i);

    for (int i = 1; i <= m; i++) cout << ans[i] << " ";
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> va[i][j];
            }
        }

        solve();
    }

    return 0;
}