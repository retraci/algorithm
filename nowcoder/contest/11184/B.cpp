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
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 2e6 + 10;

int n;
int va[N];
int vis[N];

void solve() {
    vector<int> ans(n + 1);
    ans[1] = va[1];
    vis[va[1]] = 1;
    vector<int> cnt(n + 1, 1);
    int s = va[1];
    for (int i = 2; i <= n; i++) {
        int x = va[i];
        int gcd = __gcd(s, x);
        if (gcd == 1) break;

        while (vis[cnt[x] * x]) cnt[x]++;
        int ai = cnt[x] * x;
        vis[ai] = 1;
        ans[i] = ai;
    }

    int ai = 1;
    for (int i = 1; i <= n; i++) {
        if (ans[i] != 0) continue;

        while (ai <= n && vis[ai]) ai++;
        ans[i] = ai;
        vis[ai] = 1;
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}