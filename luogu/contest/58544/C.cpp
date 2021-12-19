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
#include <numeric>
#include <cmath>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1010;

int n;
double va[N];
int ans[N];

void solve() {
    double mx = *max_element(va + 1, va + n + 1);
    double mi = *min_element(va + 1, va + n + 1);

    for (int i = 1; i <= n; i++) {
        ans[i] = floor(100.0 * (va[i] - mi) / (mx - mi));
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
    for (int i = 1; i <= n; i++) {
        cin >> va[i];
    }
    solve();

    return 0;
}