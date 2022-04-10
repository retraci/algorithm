#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>

using namespace std;

#define ll long long

ll a, b, n;

void solve() {
    int ans = 0;
    ll s = 0;
    for (int i = 0; i < n; i++) {
        int c = i % 7;
        if (c + 1 <= 5) s += a;
        else s += b;
        if (s >= n) {
            ans = i + 1;
            break;
        }
    }

    cout << ans << "\n";
}

int main() {
//    freopen("../in.txt", "r", stdin);
    freopen("../dp.in", "r", stdin);
    freopen("../dp.out", "w", stdout);

    int T;
    cin >> T;
    while (T--) {
        cin >> a >> b >> n;
        solve();
    }

    return 0;
}
