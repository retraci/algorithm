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

const int N = 100010;

int n, K;
ll va[N];

void solve() {
    priority_queue<pll> que;
    for (int i = 1; i <= n; i++) {
        que.push({-va[i], 0});
    }
    while ((n - 1) % (K - 1)) que.push({0, 0}), n++;

    ll ans = 0;
    while (que.size() > 1) {
        ll sum = 0, dep = 0;
        for (int i = 1; i <= K; i++) {
            auto [w, d] = que.top(); que.pop(); w = -w, d = -d;
            sum += w;
            dep = max(dep, d);
        }
        ans += sum;
        que.push({-sum, -(dep + 1)});
    }

    cout << ans << endl;
    cout << -que.top().second << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}