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

ll a, b;
vector<ll> va;

void divide(ll x) {
    for (ll i = 1; 1LL * i * i <= x; i++) {
        if (x % i == 0) {
            va.push_back(i);
            if (i * i != x) va.push_back(x / i);
        }
    }
}

void init() {
    ll gc = __gcd(a, b);
    divide(gc);
    sort(va.begin(), va.end());
}

void solve() {
    init();

    int q;
    cin >> q;
    while (q--) {
        ll L, R;
        cin >> L >> R;
        auto it = upper_bound(va.begin(), va.end(), R);
        if (it == va.begin()) {
            cout << -1 << "\n";
            continue;
        }

        it = prev(it);
        ll x = *it;
        if (x >= L && x <= R) cout << x << "\n";
        else cout << -1 << "\n";
    }
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