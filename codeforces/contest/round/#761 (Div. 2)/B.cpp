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

int n;

void solve() {
    int a, b;
    if (n & 1) {
        int tmp = n / 2;
        if (tmp & 1) {
            a = tmp + 2, b = tmp - 2;
        } else {
            a = tmp + 1, b = tmp - 1;
        }
    } else {
        a = n / 2, b = n / 2 - 1;
    }

    cout << a << " " << b << " " << 1 << "\n";
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