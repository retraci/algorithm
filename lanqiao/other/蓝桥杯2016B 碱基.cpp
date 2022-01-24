// // 蓝桥杯2016B 碱基
/*
	思路：
	枚举
*/

#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

int n, m, k;
vector<string> v;

void solve() {
	int ans = 0;

	if(m == 2) {
		for(int i1 = 0; i1 < n; i1++) {
			for(int s1 = 0; s1+k<=v[i1].size(); s1++) {
				string str1 = v[i1].substr(s1, k);

				for(int i2 = i1+1; i2 < n; i2++) {
					for(int s2 = 0; s2+k<=v[i2].size(); s2++) {
						string str2 = v[i2].substr(s2, k);

						if(str1 == str2) ans = (ans+1) % MOD;
					}
				}
			}
		}
	}

	if(m == 3) {
		for(int i1 = 0; i1 < n; i1++) {
			for(int s1 = 0; s1+k<=v[i1].size(); s1++) {
				string str1 = v[i1].substr(s1, k);

				for(int i2 = i1+1; i2 < n; i2++) {
					for(int s2 = 0; s2+k<=v[i2].size(); s2++) {
						string str2 = v[i2].substr(s2, k);
						if(str1 != str2) continue;
						
						for(int i3 = i2+1; i3 < n; i3++) {
							for(int s3 = 0; s3+k<=v[i3].size(); s3++) {
								string str3 = v[i3].substr(s3, k);

								if(str1 == str3) ans = (ans+1) % MOD;
							}
						}
					}
				}
			}
		}
	}


	cout << ans << endl;
}

int main() {
	cin >> n >> m >> k;

	string temp;
	for(int i = 0; i < n; i++) {
		cin >> temp;
		v.push_back(temp);
	}
	solve();

	return 0;
}
