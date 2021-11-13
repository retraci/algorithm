#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 22;

int n;
int fa[N];
vector<int> son[22];

vector<int> dfs(int u) {
    vector<int> res;

    for (int v : son[u]) {
        vector<int> temp = res, cur = dfs(v);
        for (int i = 0; i < cur.size(); i++) {
            temp.push_back(cur[i]);
            if (i & 1) temp.insert(temp.end(), res.begin(), res.end());
            else temp.insert(temp.end(), res.rbegin(), res.rend());
        }
        res = temp;
    }

    res.insert(res.begin(), u);
    return res;
}

void solve() {
    for (int i = 2; i <= n; i++) son[fa[i]].push_back(i);

    vector<int> ans = dfs(1);
    ans.erase(ans.begin());
    cout << ans.size() << endl;
    for (int u : ans) cout << u << " ";
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 2; i <= n; i++) cin >> fa[i];
    solve();

    return 0;
}