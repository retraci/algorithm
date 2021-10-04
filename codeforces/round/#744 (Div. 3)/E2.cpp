#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

const int N = 2e5 + 10;

typedef pair<int, int> pii;

int n;
int va[N];

void solve() {
    tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> tr;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int c1 = tr.order_of_key({va[i], -1}), c2 = i - tr.order_of_key({va[i], n});
        ans += min(c1, c2);
        tr.insert({va[i], i});
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> va[i];
        solve();
    }

    return 0;
}