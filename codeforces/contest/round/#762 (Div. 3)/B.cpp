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

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

ll n;

void solve() {
    ll a, b, c;
    {
        ll left = 0, right = 1e5;
        while (left < right) {
            ll mid = left + right + 1 >> 1;
            ll y = mid * mid;
            if (y <= n) left = mid;
            else right = mid - 1;
        }
        a = left;
    }

    {
        ll left = 0, right = 1e5;
        while (left < right) {
            ll mid = left + right + 1 >> 1;
            ll y = mid * mid * mid;
            if (y <= n) left = mid;
            else right = mid - 1;
        }
        b = left;
    }

    {
        ll left = 0, right = 1e3;
        while (left < right) {
            ll mid = left + right + 1 >> 1;
            ll y = mid * mid * mid * mid * mid * mid;
            if (y <= n) left = mid;
            else right = mid - 1;
        }
        c = left;
    }

    cout << a + b - c << "\n";
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
        cin >> n;
        solve();
    }

    return 0;
}