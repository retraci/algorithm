#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 2e5 + 10;

ll B, L;
ll va[N];

void solve() {
    ll md = 0;
    for (int i = 1; i <= L; i++) {
        md = (md * B + va[i]) % (B + 1);
    }
    if (md == 0) {
        cout << 0 << " " << 0 << endl;
        return;
    }

    int need1 = md, need0 = B + 1 - md;
//    cout << need1 << " " << need0 << endl;
    for (int i = 1; i <= L; i++) {
        int id = L - i + 1;
        if (id & 1) {
            if (va[i] >= need1) {
                cout << i << " " << va[i] - need1 << endl;
                return;
            }
        } else {
            if (va[i] >= need0) {
                cout << i << " " << va[i] - need0 << endl;
                return;
            }
        }
    }

    cout << -1 << " " << -1 << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> B >> L;
    for (int i = 1; i <= L; i++) cin >> va[i];
    solve();

    return 0;
}