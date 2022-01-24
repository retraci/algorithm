// 合成数 
/*

*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 210;
const long long MOD = 1000000007; 

int n;
long long a[maxn];
int vis[maxn];

vector<int> get_vec(long long x) {
	vector<int> res;
	while(x) {
		long long temp = x % 10;
		res.push_back(temp);
		x /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}

bool cmp(long long a, long long b) {
	vector<int> va = get_vec(a);
	vector<int> vb = get_vec(b);
	
	int i = 0;
	while(i < va.size() && i < vb.size()) {
		if(va[i] > vb[i]) return true;
		else if(va[i] < vb[i]) return false;
		i++;
	}
	
	if(va.size() < vb.size()) return false;
	return true;
}

long long get_x(long long x) {
	long long temp = 0;
	while(x) {
		temp++;
		x /= 10;
	}
	
	long long res = 1;
	while(temp--) {
		res *= 10;
	}
	
	return res;
}

int main() {
	cin >> n;
	
	for(int i = 0; i < n; i++) {
		scanf("%I64d", &a[i]);
	}

	long long ans = 0;
	memset(vis, 0, sizeof(vis));
	for(int i = 0; i < n; i++) {
		long long cur = -1;
		for(int j = 0; j < n; j++) {
			if(vis[j]) continue;
			if(cur == -1) {
				cur = j;
				continue;
			}
			if(a[j] == a[cur]) continue;
			
			if(cmp(a[j], a[cur])) {
				cur = j;
			}
		}
		
		long long x = get_x(a[cur]);
		x %= MOD;
		ans = (ans * x) % MOD;
		ans = (ans + a[cur]) % MOD;
		vis[cur] = 1;
	}
	cout << ans << endl;
	
	return 0;
} 
