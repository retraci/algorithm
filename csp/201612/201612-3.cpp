// 201612-3 权限查询
/*

*/

#include <bits/stdc++.h>

using namespace std;

struct privilege {
	string name;
	int level;
	privilege(string s_, int l_) {
		name = s_;
		level = l_;
	}
};

int num_p, num_r, num_u;
map<string, vector<string> > users;
map<string, vector<privilege> > roles;

int query(string u_name, privilege& p) {
	vector<string> rs = users[u_name];
	
	int res = -2;
	for(int i = 0; i < rs.size(); i++) {
		vector<privilege> ps = roles[rs[i]];
		for(int j = 0; j < ps.size(); j++) {
			privilege &tmp = ps[j];
			if(tmp.name == p.name) {
				res = max(res, tmp.level);
			}
		}
	}
	
	return res;
}

void solve() {
	string str;
	string u_name, r_name, p_name;
	int level;
	int q_num;

	cin >> q_num;

	while(q_num--) {
		cin >> u_name;
		cin >> str;
		if(str.find(':') != str.npos) {
			stringstream ss;
			str[str.find(':')] = ' ';
			ss << str;
			ss >> p_name;
			ss >> level;
		} else {
			p_name = str;
			level = -1;
		}
		privilege p = privilege(p_name, level);
		
		int ans = query(u_name, p);
		if(level == -1) {
			if(ans == -1) {
				cout << "true" << endl;
			}
			else if(ans == -2) {
				cout << "false" << endl;
			} else {
				cout << ans << endl;
			}
		} else {
			if(ans >= level) {
				cout << "true" << endl;
			} else {
				cout << "false" << endl;
			}
		}
	}
}

int main() {
	string u_name, r_name, p_name;
	int p_n, r_n;

	cin >> num_p;
	string str;
	while(num_p--) {
		cin >> str;
	}

	cin >> num_r;
	int level;
	for(int i = 0; i < num_r; i++) {
		cin >> r_name;
		cin >> p_n;

		vector<privilege> ps;
		while(p_n--) {
			cin >> str;
			if(str.find(':') != str.npos) {
				stringstream ss;
				str[str.find(':')] = ' ';
				ss << str;
				ss >> p_name;
				ss >> level;
//				cout << p_name << level << endl;
				ps.push_back(privilege(p_name, level));
			} else {
				ps.push_back(privilege(str, -1));
			}
		}

		roles[r_name] = ps;
	}

//	cout << endl;
//	map<string, vector<privilege> >::iterator it;
//	for(it=rs.begin(); it!=rs.end(); it++) {
//		cout << it->first << endl;
//		vector<privilege> v = it->second;
//		for(int i = 0; i < v.size(); i++) {
//			cout << v[i].name << " " << v[i].level << endl;
//		}
//		cout << endl;
//	}

	cin >> num_u;
	for(int i = 0; i < num_u; i++) {
		cin >> u_name;
		cin >> r_n;

		vector<string> rs;
		while(r_n--) {
			cin >> str;
			rs.push_back(str);
		}
		users[u_name] = rs;
	}

//	cout << endl;
//	map<string, vector<string> >::iterator it;
//	for(it=users.begin(); it!=users.end(); it++) {
//		cout << it->first << endl;
//		vector<string> v = it->second;
//		for(int i = 0; i < v.size(); i++) {
//			cout << v[i] << " ";
//		}
//		cout << endl;
//	}

	solve();

	return 0;
}
