#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1e6 + 10, M = 9000;

int n;
int va[N], r[M];
int ans[N];
vector<int> g[M];

void solve() {
    for (int i = 0; i < M; i++) g[i].push_back(0);
    for (int i = 0; i < M; i++) r[i] = M - 1;

    ans[0] = 1;
    for (int i = 1; i <= n; i++) {
        int a = va[i];
        for (int x : g[a]) {
            int to = x ^ a;
            ans[to] = 1;
            while (r[to] > a) {
                g[r[to]].push_back(to);
                r[to]--;
            }
        }
        // 下一个 a 没必要把之前的再推一次
        g[a] = {};
    }

    int cnt = 0;
    for (int i = 0; i < M; i++) cnt += ans[i];
    cout << cnt << endl;
    for (int i = 0; i < M; i++) {
        if (ans[i]) cout << i << " ";
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}