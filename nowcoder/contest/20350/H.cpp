#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>

using namespace std;

unordered_map<string, string> mp = {
        {"chimasu", "tte"},
        {"rimasu", "tte"},
        {"mimasu", "nde"},
        {"bimasu", "nde"},
        {"nimasu", "nde"},
        {"kimasu", "ite"},
        {"gimasu", "ide"},
        {"shimasu", "shite"}
};

string str;

void solve() {
    if (str == "ikimasu") {
        cout << "itte" << endl;
        return;
    }

    for (auto &[k, v] : mp) {
        auto p = str.find(k);
        if (p != -1 && p + k.size() == str.size()) {
            cout << str.substr(0, p) + v << endl;
            continue;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> str;
        solve();
    }

    return 0;
}
