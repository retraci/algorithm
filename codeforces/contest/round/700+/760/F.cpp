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
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

ll a, b;
unordered_set<ll> st;

ll rev(ll x) {
    ll res = 0;
    while (x) {
        res <<= 1;
        res += x & 1;
        x >>= 1;
    }
    return res;
}

ll get(ll x) {
    ll res = 0;
    while (x) {
        res++;
        x >>= 1;
    }
    return res;
}

bool dfs(ll u) {
    if (st.count(u) || get(u) > get(b)) return false;
    if (u == b) return true;
    st.insert(u);

    return dfs(rev(u * 2)) || dfs(rev(u * 2 + 1));
}

void solve() {
    if (a == b) {
        cout << "YES" << "\n";
        return;
    }
    bool ans = dfs(rev(a * 2)) || dfs(rev(a * 2 + 1));
    cout << (ans ? "YES" : "NO") << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> a >> b;
    solve();

    return 0;
}