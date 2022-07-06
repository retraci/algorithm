#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int a, b, ab, ba;
string s;

void solve() {
    if (count(s.begin() + 1, s.end(), 'A') != a + ab + ba || count(s.begin() + 1, s.end(), 'B') != b + ab + ba) {
        cout << "NO" << "\n";
        return;
    }

    int n = s.size() - 1;
    vector<int> AB, BA, odd;
    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j + 1 <= n && s[j] != s[j + 1]) j++;

        int len = j - i + 1;
        if (len & 1) {
            odd.push_back(len / 2);
        } else {
            if (s[i] == 'A') AB.push_back(len / 2);
            else BA.push_back(len / 2);
        }

        i = j;
    }

    int cAB = accumulate(AB.begin(), AB.end(), 0);
    int cBA = accumulate(BA.begin(), BA.end(), 0);
    for (int x : odd) {
        int t = min(max(0, ab - cAB), x);
        cAB += t;
        cBA += x - t;
    }

    sort(AB.rbegin(), AB.rend());
    sort(BA.rbegin(), BA.rend());
    for (int x : AB) {
        if (cAB > ab) {
            cAB--, x--;
            int t = min(cAB - ab, x);
            cAB -= t;
            cBA += t;
        }
    }
    for (int x : BA) {
        if (cBA > ba) {
            cBA--, x--;
            int t = min(cBA - ba, x);
            cBA -= t;
            cAB += t;
        }
    }

    cout << (cAB >= ab && cBA >= ba ? "YES" : "NO") << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        cin >> a >> b >> ab >> ba;
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}