// 重复元素全排列
/*
	leetcode_47
*/

#include <iostream>
#include <algorithm>
#include <vector> 

using namespace std;

// 
void perm(vector<int>& v, int idx, vector<int>& p) {
	if(idx == v.size()) {
		ans.emplace_back(p);
		return;
	}
	for(int i = 0; i < v.size(); i++) {
		// 如果选过  或者  这一轮已经选过相同的元素 
		if(vis[i] || (i>0 && v[i] == v[i-1] && !vis[i-1]))
			continue;
		vis[i] = 1;
		p.emplace_back(v[i]);
		perm(v, idx+1, p);
		vis[i] = 0;					// 由于回溯，上面的 vis[i-1] 是等于 0 
		p.pop_back();
	}
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
	vector<int> p;
	vis.resize(nums.size());
	sort(nums.begin(), nums.end());
	perm(nums, 0, p);
	return ans;
}

