#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

ll n, m;
ll va[N];
ll s[N];

int calc(int mid) {
    priority_queue<pll> que;
    for (int i = 1; i <= mid - 1; i++) que.push({-s[i], i});

    for (int i = mid; i <= n; i++) {
        que.push({-s[i], i});
        int lb = i - mid + 1;
        while (que.top().second < lb) que.pop();
        auto [w, id] = que.top(); w = -w;
        if (w - s[lb - 1] + m >= 0) return lb;
    }

    return 0;
}

void solve() {
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + va[i];

    int left = 0, right = n;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (calc(mid) > 0) left = mid;
        else right = mid - 1;
    }

    if (left == 0) {
        cout << -1 << endl;
        return;
    }

    int lb = calc(left), rb = lb + left - 1;
    cout << lb << " " << rb << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}