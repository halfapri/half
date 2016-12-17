#include<bits/stdc++.h>
using namespace std;
string s , t ;
string st ;

bool work1 (int i) {
	string ts ;
	ts.push_back (t[i]) ;
	i ++ ;
	bool flag = 0 ;
	for (; i < s.size() ; i ++) {
		if (t[i] == 'a') ts.push_back ('a') ;
		else {
			flag = 1 ;
			ts.push_back ('a') ;
		}
	}
	if (flag) {
		cout << st << ts << endl ;
		return true ;
	}
	return false ;
}

bool work2 (int i) {
	string ts ;
	ts.push_back (s[i]) ;
	i ++ ;
	bool flag = 0 ;
	for (; i < s.size () ; i ++) {
		if (s[i] == 'z') ts.push_back ('z') ;
		else {
			flag = 1 ;
			ts.push_back ('z') ;
		}
	}
	if (flag) {
		cout << st << ts << endl ;
		return true ;
	}
	return false ;
}

int main () {
	cin >> s >> t ;
	bool flag = 0 ;
	int i ;
	for (i = 0 ; i < s.size() ; i ++) {
		if (s[i] != t[i]) break ;
		st.push_back (s[i]) ;
	}
	if (t[i]-s[i]>1) {
		st.push_back (s[i]+1) ;
		i ++ ;
		for (; i < s.size() ; i ++) {
			st.push_back (s[i]) ;
		}
		cout << st << endl ;
	}
	else {
		if (work1(i)) ;
		else if (work2(i) == 0) puts ("No such string") ;
	}
	return 0 ;
}
