#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> path;
int vis[20];

void dfs(int k) {
    if (k > n) {
        for (int &x: path) printf("%d ", x);
        printf("\n");
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;

        vis[i] = 1;
        path.push_back(i);
        dfs(k + 1);
        path.pop_back();
        vis[i] = 0;
    }
}

void solve() {
    dfs(1);
}

int main() {
    cin >> n;
    solve();

    return 0;
}
