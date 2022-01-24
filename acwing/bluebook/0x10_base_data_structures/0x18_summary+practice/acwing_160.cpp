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
#define ull unsigned long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 200010;
const ull BASE = 131;

int n, m, q;
string s1, s2;

ull h1[N], h2[N], p[N];
int cnt[N];

void init() {
    p[0] = 1;
    for (int i = 1; i <= max(n, m); i++) p[i] = p[i - 1] * BASE;
    for (int i = 1; i <= n; i++) h1[i] = h1[i - 1] * BASE + s1[i];
    for (int i = 1; i <= m; i++) h2[i] = h2[i - 1] * BASE + s2[i];
}

int get(ull *h, int L, int R) {
    return h[R] - h[L - 1] * p[R - L + 1];
}

bool check(int s, int x) {
    int lb1 = s, rb1 = s + x - 1;
    int lb2 = 1, rb2 = x;

    return get(h1, lb1, rb1) == get(h2, lb2, rb2);
}

void solve() {
    init();

    for (int i = 1; i <= n; i++) {
        int left = 0, right = min(m, n - i + 1);
        while (left < right) {
            int mid = left + right + 1 >> 1;
            if (check(i, mid)) left = mid;
            else right = mid - 1;
        }

        cnt[left]++;
    }

    while (q--) {
        int x;
        cin >> x;
        cout << cnt[x] << "\n";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> q;
    cin >> s1 >> s2;
    s1 = ' ' + s1, s2 = ' ' + s2;
    solve();

    return 0;
}