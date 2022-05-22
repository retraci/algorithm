// region kmp
// s 下标从 1 开始
vector<int> get_ne(const string &s) {
    int n = s.size() - 1;
    vector<int> ne(n + 1, 0);
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[i] != s[j + 1]) j = ne[j];
        if (s[i] == s[j + 1]) j++;
        ne[i] = j;
    }

    return ne;
}

// t 里面 出现 s
int qr(const string &t, const string &s) {
    vector<int> ne = get_ne(s);
    int n = t.size() - 1, m = s.size() - 1;
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && t[i] != s[j + 1]) j = ne[j];
        if (t[i] == s[j + 1]) j++;

        if (j == m) {
            cout << i - m << " ";
            j = ne[j];
        }
    }

    return -1;
}
// endregion
