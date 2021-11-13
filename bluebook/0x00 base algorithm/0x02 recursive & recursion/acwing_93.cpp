#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> path;

void dfs(int now) {
    if (path.size() >= m) {
        for (int &x: path) printf("%d ", x);
        printf("\n");
        return;
    }
    if (now > n || path.size() + (n - now + 1) < m) return;

    path.push_back(now);
    dfs(now+1);
    path.pop_back();

    dfs(now+1);
}

void solve() {
    dfs(1);
}

int main() {
    cin >> n >> m;
    solve();

    return 0;
}
