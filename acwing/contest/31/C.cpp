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

struct Circle {
    ll r, x, y;
};

const int N = 1010;

int n, m, K;
pll ps[N];
Circle cs[N];
bitset<N> va[N];

ll dist2(ll x1, ll y1, ll x2, ll y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

bool check(Circle &c, pll &p) {
    auto &[r, x1, y1] = c;
    auto &[x2, y2] = p;
    ll d2 = dist2(x1, y1, x2, y2);
    return d2 <= r * r;
}

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (check(cs[j], ps[i])) {
                va[i][j] = 1;
            }
        }
    }
}

void solve() {
    init();

    while (K--) {
        ll a, b;
        cin >> a >> b;
        bitset<N> tmp = va[a] ^ va[b];
        cout << tmp.count() << "\n";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> K;
    for (int i = 1; i <= n; i++) {
        ll x, y;
        cin >> x >> y;
        ps[i] = {x, y};
    }
    for (int i = 1; i <= m; i++) {
        ll r, x, y;
        cin >> r >> x >> y;
        cs[i] = {r, x, y};
    }
    solve();

    return 0;
}