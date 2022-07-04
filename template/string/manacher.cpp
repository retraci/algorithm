// region 马拉车
template<int SZ>
struct Manacher {
    int p[2 * SZ + 10];
    string ns;

    Manacher() {}

    // 下标 0 开始
    void init(const string &s) {
        int m = s.size();
        ns.resize(m * 2 + 3);
        ns[0] = '$', ns.back() = '^';
        ns[1] = '#';
        for (int i = 0; i < m; i++) ns[i * 2 + 2] = s[i], ns[i * 2 + 3] = '#';

        int mr = 0, mid = 0;
        for (int i = 1; i < ns.size(); i++) {
            if (i < mr) p[i] = min(p[mid * 2 - i], mr - i);
            else p[i] = 1;
            while (ns[i - p[i]] == ns[i + p[i]]) p[i]++;
            if (mr < i + p[i]) {
                mr = i + p[i];
                mid = i;
            }
        }
    }
};
// endregion