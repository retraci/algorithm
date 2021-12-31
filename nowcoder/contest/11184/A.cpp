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

ll d;
int vis[32];

void solve() {
    for (int i = 0; i <= 31; i++) {
        if (d >> i & 1) vis[i] = 1;
    }

    int s = accumulate(vis, vis + 32, 0);
    if (s * 2 < 3) {
        cout << -1 << "\n";
        return;
    }

    int a = 0, b = 0, c = 0;
    for (int i = 0; i <= 31; i++) {
        if (vis[i]) {
            a += 1 << i;
            if (c == 0) {
                c += 1 << i;
            } else {
                b += 1 << i;
            }
        }
    }

//    cout << (a ^ b ^ c) << " " << (a | b | c) << "\n";
    cout << a << " " << b << " " << c << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> d;
    solve();

    return 0;
}