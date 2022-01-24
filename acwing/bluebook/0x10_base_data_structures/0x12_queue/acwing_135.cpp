#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <limits.h>

using namespace std;

const int N = 300010;

int n, m;
int vv[N];

void solve() {
    for (int i = 1; i <= n; i++) vv[i] += vv[i - 1];

    int ans = INT_MIN;
    deque<int> que;
    que.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (que.size() && i - que.front() > m) que.pop_front();
        if (que.size()) ans = max(ans, vv[i] - vv[que.front()]);
        while (que.size() && vv[i] <= vv[que.back()]) que.pop_back();
        que.push_back(i);
    }
    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", &vv[i]);
    solve();

    return 0;
}