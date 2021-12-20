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

int n, m, K;

void solve() {
    int cur = 0;
    int up = n % m, down = m - up;

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < down; j++) {
            int cnt = n / m;
            cout << cnt << " ";
            for (int k = 0; k < cnt; k++) {
                cout << cur + 1 << " ";
                cur = (cur + 1) % n;
            }
            cout << "\n";
        }

        int s = cur;
        for (int j = 0; j < up; j++) {
            int cnt = n / m + 1;
            cout << cnt << " ";
            for (int k = 0; k < cnt; k++) {
                cout << s + 1 << " ";
                s = (s + 1) % n;
            }
            cout << "\n";
        }
    }
    cout << "\n";
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
        cin >> n >> m >> K;
        solve();
    }

    return 0;
}