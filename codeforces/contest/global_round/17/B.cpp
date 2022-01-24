#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

int n;
int va[N];

bool check(vector<int> &vb) {
    int lb = 0, rb = vb.size() - 1;
    while (lb < rb) {
        if (vb[lb] == vb[rb]) {
            lb++, rb--;
            continue;
        } else {
            return false;
        }
    }

    return true;
}

void solve() {
    int lb = 1, rb = n;
    while (lb < rb) {
        if (va[lb] == va[rb]) {
            lb++, rb--;
            continue;
        }

        vector<int> vb;
        for (int i = 1; i <= n; i++) {
            if (va[lb] == va[i]) continue;
            vb.push_back(va[i]);
        }
        if (check(vb)) {
            cout << "YES" << endl;
            return;
        }

        vb = {};
        for (int i = 1; i <= n; i++) {
            if (va[rb] == va[i]) continue;
            vb.push_back(va[i]);
        }
        if (check(vb)) {
            cout << "YES" << endl;
            return;
        }

        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
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
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}