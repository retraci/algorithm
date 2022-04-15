// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> res;
        for (int i = 1; i <= N; i++) {
            int left = 0, right = i - 1;
            while (left < right) {
                int md = left + right >> 1;
                if (compare(i, res[md])) right = md;
                else left = md + 1;
            }

            res.insert(res.begin() + left, i);
        }

        return res;
    }
};