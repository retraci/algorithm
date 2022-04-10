#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>

using namespace std;

const int N = 10010;

int n;
int ans[N];

void solve() {
    for (int i = 1; i <= n; i++) {
        int lb = i - 1, rb = n - i;
        ans[i] = 2 * max(lb, rb);
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i];
        if (i != n) cout << "\n";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    solve();

    return 0;
}
