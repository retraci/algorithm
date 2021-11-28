#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll a, b;

void solve() {
    string s1 = to_string(a), s2 = to_string(b);
    reverse(s1.begin(), s1.end()), reverse(s2.begin(), s2.end());

    for (int i = 0; i < min(s1.size(), s2.size()); i++) {
        int x1 = s1[i] - '0', x2 = s2[i] - '0';
        if (x1 + x2 > 9) {
            cout << "Hard" << endl;
            return;
        }
    }
    cout << "Easy" << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> a >> b;
    solve();

    return 0;
}