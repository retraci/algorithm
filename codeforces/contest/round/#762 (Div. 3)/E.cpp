#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 2e5 + 10;

int n;
int va[N];
ll cnt[N];
ll ans[N];

void solve() {
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; i++) cnt[va[i]]++;

    priority_queue<int> que;
    ll cur = 0;
    for (int i = 0; i <= n; i++) {
        ans[i] = cur + cnt[i];

        if (cnt[i] == 0) {
            if (!que.empty()) {
                cur += i - que.top();
                que.pop();
            } else {
                for (int k = i + 1; k <= n; k++) ans[k] = -1;
                break;
            }
        } else if (cnt[i] > 1) {
            for (int k = 0; k < cnt[i] - 1; k++) que.push(i);
        }
    }

    for (int i = 0; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}