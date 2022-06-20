#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll n;

void solve() {
    cout << -(n - 1) << " " << n << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif


    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        solve();
    }

    return 0;
}
