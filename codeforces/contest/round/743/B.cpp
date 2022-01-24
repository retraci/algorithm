#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

struct Node {
    ll cost, idx;
    bool operator< (const Node &that) const {
        return cost < that.cost;
    }
};

int n;
int va[N], vb[N];
ll na[N], nb[N];
set<Node> st;

void solve() {
    for (int i = 0; i < n; i++) {
        na[va[i] / 2] = i;
    }
    for (int i = 0; i < n; i++) {
        nb[(vb[i] - 1) / 2] = i;
    }

    for (int i = 0; i < n; i++) st.insert({nb[i], i});

    ll ans = 1e18;
    for (int i = 0; i < n; i++) {
        ll tmp = na[i] + st.begin()->cost;
        st.erase({nb[i], i});
        ans = min(ans, tmp);
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
        for (int i = 0; i < n; i++) cin >> vb[i];
        solve();
    }

    return 0;
}