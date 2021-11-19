#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;

const int N = 1e6 + 10;

int n;
string s;
int c[N];
vector<int> v1;

bool check(int x) {
    int lst = 0;
    int d = v1[0] - lst - 1;
    //cout << x << " " << d << "#\n";
    if (d > x) {
        return false;
    } else {
        if (d == x) lst = v1[0] + x - 1;
        else lst = v1[0] + x;
    }
    int vn = v1.size();
    for (int i = 1; i < vn; i++) {
        d = v1[i] - lst - 1;
        //cout << lst << " " << d << " " << x << "\n";
        if (d > x) return false;
        if (d == x) lst = v1[i] + x - 1;
        else lst = v1[i] + x;
    }
    if (lst < n) return false;
    return true;
}

void solve() {
    s = " " + s;
    v1 = vector < int > {};
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') v1.push_back(i);
    }
    if (v1.size() == n) {
        cout << 0 << "\n";
        return;
    }

    int left = 0, right = 1e6;
    while (left < right) {
        int mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }
    cout << left << endl;
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
        cin >> s;
        solve();
    }

    return 0;
}