#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> path;

void dfs(int now) {
    if (now > n) {
        for (int &x: path) printf("%d ", x);
        printf("\n");
        return;
    }

    dfs(now+1);

    path.push_back(now);
    dfs(now+1);
    path.pop_back();
}

void solve() {
    dfs(1);
}

int main() {
    cin >> n;
    solve();

    return 0;
}
