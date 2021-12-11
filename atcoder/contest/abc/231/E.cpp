#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 66;

ll n, m;
ll va[N];
map<pll, ll> memo;

ll dfs(ll id, ll rem) {
    if (memo.count({id, rem})) return memo[{id, rem}];
    if (id == 1) return rem;

    ll res = min(dfs(id - 1, rem % va[id]) + rem / va[id],
                 dfs(id - 1, va[id] - rem % va[id]) + rem / va[id] + 1);

    return memo[{id, rem}] = res;
}

void solve() {
    cout << dfs(n, m) << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}