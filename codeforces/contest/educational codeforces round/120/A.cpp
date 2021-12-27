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

int va[3];

void solve() {
    sort(va, va + 3);

    if (va[0] + va[1] == va[2]) {
        cout << "YES" << "\n";
        return;
    }

    int s = va[0] ^ va[1] ^ va[2];
    for (int i = 0; i < 3; i++) {
        if (~va[i] & 1) {
            if ((s ^ va[i]) == 0) {
                cout << "YES" << "\n";
                return;
            }
        }
    }

    cout << "NO" << "\n";
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
        cin >> va[0] >> va[1] >> va[2];
        solve();
    }

    return 0;
}