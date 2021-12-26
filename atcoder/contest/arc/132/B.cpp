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
int va[N], vb[N];

void solve() {
    int ans = 1e9;

    if (va[1] == 1 && va[n] == n) {
        cout << 0 << "\n";
        return;
    }

    {
        for (int i = 1; i <= n; i++) vb[i] = vb[i + n] = va[i];

        int id = max_element(va + 1, va + n + 1) - va;
        if (vb[id] > vb[id + 1]) ans = min(ans, id - 1 + 1);
        else ans = min(ans, id);
    }
    reverse(va + 1, va + n + 1);
    {
        for (int i = 1; i <= n; i++) vb[i] = vb[i + n] = va[i];

        int id = max_element(va + 1, va + n + 1) - va;
        if (vb[id] > vb[id + 1]) ans = min(ans, id - 1 + 1 + 1);
        else ans = min(ans, id + 1);
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
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}