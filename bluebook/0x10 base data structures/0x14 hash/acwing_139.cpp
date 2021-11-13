#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ull unsigned long long

const int N = 2000010;
const ull BASE = 131;

int T;
int n;
string s;
ull hl[N], hr[N], p[N];

ull get_hash(ull *arr, int L, int R) {
    return arr[R] - arr[L - 1] * p[R - L + 1];
}

int get_ridx(int id) {
    return n - id + 1;
}

void solve() {
    string tmp = "";
    for (char ch : s) tmp += "#", tmp += ch;
    tmp += "#";
    s = tmp;

    n = s.size();
    p[0] = 1;
    for (int i = 1, j = n; i <= n; i++, j--) {
        hl[i] = hl[i - 1] * BASE + s[i - 1] - 'a';
        hr[i] = hr[i - 1] * BASE + s[j - 1] - 'a';
        p[i] = p[i - 1] * BASE;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int left = ans, right = min(i - 1, n - i);
        while (left < right) {
            int mid = left + right + 1 >> 1;
            if (get_hash(hl, i - mid, i - 1) == get_hash(hr, get_ridx(i + mid), get_ridx(i + 1))) left = mid;
            else right = mid - 1;
        }

        ans = max(ans, left);
    }

    cout << "Case " << ++T << ": " << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    while (cin >> s, s != "END") {
        solve();
    }

    return 0;
}