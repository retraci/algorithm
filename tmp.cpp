#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void solve() {

}

using namespace std;
const int xn = 2e5 + 10;

int qq, n, a[xn], ans, res, ptr;

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> qq;
    while (qq--) {
        cin >> n, ans = 0;
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= n; ++i) {
            if (a[i] == a[i - 1])
                continue;
            res = 0, ptr = i;
            while (ptr <= n) {
                cout << ptr << " " << i << endl;
                ptr = lower_bound(a + ptr + 1, a + n + 1, 2 * a[ptr] - a[i]) - a, ++res;
            }
            ans = max(ans, res);
        }
        cout << n - ans << "\n";
    }

    return 0;
}