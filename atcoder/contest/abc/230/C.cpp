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

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

ll n, a, b;
ll r1, r2, c1, c2;

void solve() {
    for (ll i = r1; i <= r2; i++) {
        for (ll j = c1; j <= c2; j++) {
            ll d1 = abs(i - a), d2 = abs(j - b);
            if (d1 == d2) cout << '#';
            else cout << '.';
        }
        cout << "\n";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> a >> b;
    cin >> r1 >> r2 >> c1 >> c2;
    solve();

    return 0;
}