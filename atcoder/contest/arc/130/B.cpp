#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 3e5 + 10;

ll h, w, C, Q;
int ts[N], ns[N], cs[N];
unordered_set<int> vr, vc;
ll ans[N];

void solve() {
    for (int i = Q; i >= 1; i--) {
        ll t = ts[i], n = ns[i], c = cs[i];

        if (t == 1) {
            ll tmp = w - vc.size();
            if (vr.count(n)) tmp = 0;
            ans[c] += tmp;
            vr.insert(n);
        } else {
            ll tmp = h - vr.size();
            if (vc.count(n)) tmp = 0;
            ans[c] += tmp;
            vc.insert(n);
        }
    }

    for (int i = 1; i <= C; i++) cout << ans[i] << " ";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> h >> w >> C >> Q;
    for (int i = 1; i <= Q; i++) cin >> ts[i] >> ns[i] >> cs[i];
    solve();

    return 0;
}