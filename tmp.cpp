#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<pair<int, int>> mx(n), mi(n);
        vector<vector<int>> ans;
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1) mx[i] = { a[i], i }, mi[i] = { a[i], i };
            else {
                if (a[i] >= mx[i + 1].first) mx[i] = { a[i], i };
                else mx[i] = mx[i + 1];
                if (a[i] <= mi[i + 1].first) mi[i] = { a[i], i };
                else mi[i] = mi[i + 1];
            }
        }
        for (int i = 0; i < n - 2; i++) {
            if (mi[i + 1].first - mx[i + 2].first < a[i]) {
                a[i] = mi[i + 1].first - mx[i + 2].first;
                ans.push_back({ i + 1, mi[i + 1].second + 1, mx[i + 2].second + 1 });
            }
            if (mi[i + 2].first - mx[i + 1].first < a[i]) {
                a[i] = mi[i + 2].first - mx[i + 1].first;
                ans.push_back({ i + 1, mi[i + 2].second + 1, mx[i + 1].second + 1 });
            }
        }
        bool flag = true;
        for (int i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) flag = false;
        }
        if (!flag) cout << "-1" << "\n";
        else {
            cout << ans.size() << "\n";
            for (int i = 0; i < ans.size(); i++) {
                cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << "\n";
            }
        }
    }
    return 0;
}