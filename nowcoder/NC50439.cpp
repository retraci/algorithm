#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

int n;
ll v[N], s[N];
int idxs[N];

bool cmp(int a, int b) {
    return s[a] > s[b];
}

void solve() {
    for (int i = 0; i < n; i++) {
        idxs[i] = i;
    }
    sort(idxs, idxs + n, cmp);

    ll ans = 0;
    ll cur = 0;
    priority_queue<ll, vector<ll>, greater<ll>> que;
    for (int i = 0; i < n; i++) {
        int idx = idxs[i];
        que.push(v[idx]);
        cur += v[idx];
        while (!que.empty() && que.size() > s[idx]) {
            ll tmp = que.top(); que.pop();
            cur -= tmp;
        }

        ans = max(ans, cur);
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld", &v[i], &s[i]);
    }
    solve();

    return 0;
}