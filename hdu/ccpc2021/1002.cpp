#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e7;

int n;
string s[105];
int a[150], as[150];
int p[N], q[N];

int gcd(int a, int b) {
    if (b) return gcd(b, a % b);
    else return a;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        int ss = 1, qq = 0, k = 0, sum = 0, ans = N;
        memset(a, 0, sizeof(a));
        memset(as, 0, sizeof(as));
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
            int m = s[i].length();
            for (int j = 0; j < m; ++j)
                a[s[i][j]] = true;
            ss = ss * s[i].length() / gcd(ss, s[i].length());
        }
        for (int i = 'a'; i <= 'z'; ++i)
            if (a[i]) qq++;
        int h = 1, t = 0;
        for (int i = 0, j = 0; i < 2 * n * ss; i++) {
            char c = s[j][k % (s[j].length())];
            as[c]++;
            if (as[c] == 1) sum++;
            while (as[p[h]] > 1) as[p[h]]--, h++;
            p[++t] = c;
            q[t] = i;
            if (sum == qq) ans = min(ans, i - q[h] + 1);
            if (j == n - 1) k++, j = 0; else j++;
        }
        cout << ans << endl;
    }
}