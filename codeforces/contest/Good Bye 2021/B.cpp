#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<char, int> pci;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

int n;
string str;

void solve() {
    vector<pci> va;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && str[j] == str[i]) j++;
        va.push_back({str[i], j - i});

        i = j - 1;
    }

    string ans = "";
    if (va[0].second >= 2) {
        cout << str.substr(0, 2) << "\n";
        return;
    }
    while (va[0].second--) ans += va[0].first;
    for (int i = 1; i < va.size(); i++) {
        if (va[i - 1].first > va[i].first) {
            while (va[i].second--) ans += va[i].first;
        } else {
            break;
        }
    }

    int m = ans.size();
    for (int i = m - 1; i >= 0; i--) {
        ans.push_back(ans[i]);
    }
    cout << ans << "\n";
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
        cin >> n >> str;
        solve();
    }

    return 0;
}