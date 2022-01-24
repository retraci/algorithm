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

int n, a, b;

void solve() {
    if (a + b > n - 2 || abs(a - b) > 1) {
        cout << -1 << "\n";
        return;
    }

    if (a == b) {
        int p1 = 1, p2 = n;
        while (a--) {
            cout << p1++ << " " << p2-- << " ";
        }
        while (p1 <= p2) {
            cout << p1 << " ";
            p1++;
        }
        cout << "\n";
    } else if (a > b) {
        int p1 = 1, p2 = n;
        while (a--) {
            cout << p1++ << " " << p2-- << " ";
        }
        while (p1 <= p2) {
            cout << p2 << " ";
            p2--;
        }
        cout << "\n";
    } else {
        int p1 = 1, p2 = n;
        while (b--) {
            cout << p2-- << " " << p1++ << " ";
        }
        while (p1 <= p2) {
            cout << p1 << " ";
            p1++;
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
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> a >> b;
        solve();
    }

    return 0;
}