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

const int N = 1e5 + 10;

int n;
ll vd[N], vp[N];
int idx[N];

void solve() {
    for (int i = 1; i <= n; i++) idx[i] = i;
    sort(idx + 1, idx + n + 1, [&](auto &lhs, auto &rhs) {
        return vd[lhs] < vd[rhs];
    });

    priority_queue<ll> que;
    ll cur = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        int id = idx[i];
        if (cur < vd[id]) {
            ans += vp[id], cur++;
            que.push(-vp[id]);
        } else if (!que.empty() && -que.top() < vp[id]) {
            ans -= -que.top(); que.pop();
            ans += vp[id];
            que.push(-vp[id]);
        }
    }

    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> vd[i] >> vp[i];
    solve();

    return 0;
}