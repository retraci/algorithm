#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

#define ll long long

const int N = 100010;
const ll MOD = 998244353;

int n;
vector<int> va[N];
unordered_map<ll, vector<vector<int>>> mp;

ll get_hash(vector<int> v1) {
    ll res1 = 0, res2 = 1;
    for (int x : v1) {
        res1 = res1 + x, res2 = (res2 * x) % MOD;
    }

    return (res1 + res2) % MOD;
}

bool check(vector<int> v1, vector<int> v2) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            // 正
            string t1 = "", t2 = "";
            for (int k = 0; k < 6; k++) {
                t1 += v1[(i + k) % 6], t2 += v2[(j + k) % 6];
            }
            if (t1 == t2) return true;
            // 反
            t1 = t2 = "";
            for (int k = 0; k < 6; k++) {
                t1 += v1[(i + k) % 6], t2 += v2[(j - k) % 6];
            }
            if (t1 == t2) return true;
        }
    }

    return false;
}

void solve() {
    int flag = 0;
    for (int i = 0; i < n; i++) {
        ll hash = get_hash(va[i]);
        for (auto v : mp[hash]) {
            if (check(va[i], v)) flag = 1;
        }
        mp[hash].push_back(va[i]);
    }

    if (flag) cout << "Twin snowflakes found." << endl;
    else cout << "No two snowflakes are alike." << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        va[i].resize(6);
        for (int j = 0; j < 6; j++) {
            cin >> va[i][j];
        }
    }
    solve();

    return 0;
}