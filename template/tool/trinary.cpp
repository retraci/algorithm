// region 三分
void work() {
    ll left = 0, right = 1e18;
    while (left + 10 < right) {
        ll mdl = (2 * left + right) / 3;
        ll mdr = (left + 2 * right) / 3;
        double v1 = calc(mdl), v2 = calc(mdr);
        if (v1 > v2) left = mdl;
        else right = mdr;
    }
    double ans = 1e18;
    for (int k = left; k <= right; k++) ans = min(ans, calc(k));
}
// endregion
