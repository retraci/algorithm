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

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

ll w, h;
vector<ll> ds, us, ls, rs;

void solve() {
    sort(ds.begin(),  ds.end());
    sort(us.begin(),  us.end());
    sort(ls.begin(),  ls.end());
    sort(rs.begin(),  rs.end());

    ll a = (ds.back() - ds[0]) * h;
    ll b = (us.back() - us[0]) * h;
    ll c = (ls.back() - ls[0]) * w;
    ll d = (rs.back() - rs[0]) * w;
    cout << max({a, b, c, d}) << "\n";
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
        ds = {}, us = {}, ls = {}, rs = {};
        cin >> w >> h;

        int k;
        cin >> k;
        while (k--) {
            ll x; cin >> x;
            ds.push_back(x);
        }

        cin >> k;
        while (k--) {
            ll x; cin >> x;
            us.push_back(x);
        }

        cin >> k;
        while (k--) {
            ll x; cin >> x;
            ls.push_back(x);
        }

        cin >> k;
        while (k--) {
            ll x; cin >> x;
            rs.push_back(x);
        }

        solve();
    }

    return 0;
}