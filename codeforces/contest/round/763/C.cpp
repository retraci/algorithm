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

const int N = 2e5 + 10;

int n;
ll va[N], vb[N];
ll bak[N];

bool check(ll mid) {
    for (int i = 1; i <= n; i++) va[i] = bak[i], vb[i] = 0;

    for (int i = n; i >= 3; i--) {
        if (va[i] + vb[i] - mid < 0) return false;

        ll rem = min(va[i], va[i] + vb[i] - mid);
        ll d = rem / 3;
        va[i] -= 3 * d;
        vb[i - 1] += d, vb[i - 2] += 2 * d;
    }

    for (int i = 1; i <= n; i++) {
        if (va[i] + vb[i] < mid) return false;
    }

    return true;
}

void solve() {
    for (int i = 1; i <= n; i++) bak[i] = va[i];

    ll left = 1, right = 1e9;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left << "\n";
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