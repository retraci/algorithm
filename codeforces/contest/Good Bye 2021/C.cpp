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

const int N = 110;

int n;
int va[N];

void solve() {
    if (n == 1) {
        cout << 0 << "\n";
        return;
    }

    int ans = 1e9;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int len = j - i;
            int kd = va[j] - va[i];

            int sum = 0;
            for (int k = 1; k <= n; k++) {
                int del = i > k ? va[i] - va[k] : va[k] - va[i];
                int gap = abs(i - k);
                if (del * len == gap * kd) continue;
                sum++;
            }

            ans = min(ans, sum);
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
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}