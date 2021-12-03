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

const int N = 1010;
const ull BASE = 131;

int n, m, a, b;
string va[N], vb[N];
ull h[N][N], p[N * N];
unordered_set<ull> st;

ull get(int r, int L, int R) {
    return h[r][R] - h[r][L - 1] * p[R - L + 1];
}

void init() {
    p[0] = 1;
    for (int i = 1; i <= n * m; i++) p[i] = p[i - 1] * BASE;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            h[i][j] = h[i][j - 1] * BASE + va[i][j];
        }
    }

    for (int j = b; j <= m; j++) {
        int L = j - b + 1, R = j;
        ull s = 0;
        for (int i = 1; i <= n; i++) {
            s = s * p[b] + get(i, L, R);
            if (i > a) s -= get(i - a, L, R) * p[a * b];
            if (i >= a) st.insert(s);
        }
    }
}

void solve() {
    init();

    int T;
    cin >> T;
    while (T--) {
        for (int i = 1; i <= a; i++) {
            cin >> vb[i];
            vb[i] = ' ' + vb[i];
        }

        ull s = 0;
        for (int i = 1; i <= a; i++) {
            for (int j = 1; j <= b; j++) {
                s = s * BASE + vb[i][j];
            }
        }
        if (st.count(s)) cout << 1 << "\n";
        else cout << 0 << "\n";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> a >> b;
    for (int i = 1; i <= n; i++) {
        cin >> va[i];
        va[i] = ' ' + va[i];
    }
    solve();

    return 0;
}