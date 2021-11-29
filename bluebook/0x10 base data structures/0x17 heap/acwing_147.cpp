#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 100010;

int n, K;
ll va[N], vb[N];
int ls[N], rs[N];

void init() {
    vb[1] = vb[n + 1] = 1e18;
    for (int i = 2; i <= n; i++) vb[i] = va[i] - va[i - 1];
    for (int i = 1; i <= n + 1; i++) {
        ls[i] = i - 1;
        rs[i] = i + 1;
    }
}

void remove(int id) {
    rs[ls[id]] = rs[id];
    ls[rs[id]] = ls[id];
}

void solve() {
    init();

    set<pll> st;
    for (int i = 1; i <= n + 1; i++) st.insert({vb[i], i});
    ll ans = 0;
    while (K--) {
        auto it = st.begin();
        auto [val, id] = *it;
        ans += val;

        int left = ls[id], right = rs[id];
        remove(left), remove(right);
        st.erase(it), st.erase({vb[left], left}), st.erase({vb[right], right});
        vb[id] = vb[left] + vb[right] - vb[id];
        st.insert({vb[id], id});
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}