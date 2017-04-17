#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vec;
const int M = 500+10;
struct AC {
	int go[M][4], fail[M], end[M];
	int o, rt;
	char a[4] = {'A', 'G', 'C', 'T'};
	int b[128];

	inline int NewNode() {
		for (int i=0; i<4; ++i) {
			go[o][i] = -1;
		}
		end[o] = 0;
		return o++;
	}

	inline void Init () {
		for (int i=0; i<4; ++i) {
			b[a[i]] = i;
		}
		o = 0;
		rt = NewNode();
	}

	inline void Ins (char *s) {
		int now = rt;
		for (; *s; ++s) {
			if (go[now][b[*s]]==-1) {
				go[now][b[*s]] = NewNode();
			}
			now = go[now][b[*s]];
		}
		end[now] ++;
	}

	inline void GetFail() {
		queue<int> q;
		for (int i=0; i<4; i++) {
			if (go[rt][i] == -1) {
				go[rt][i] = rt;
			} else {
				fail[go[rt][i]] = rt;
				q.push (go[rt][i]);
			}
		}
		while (!q.empty()) {
			int now = q.front(); q.pop();
			for (int i=0; i<4; i++) {
				if (go[now][i] == -1) {
					go[now][i] = go[fail[now]][i];
				} else {
					end[go[now][i]] += end[go[fail[now]][i]];
					fail[go[now][i]] = go[fail[now]][i];
					q.push (go[now][i]);
				}
			}
		}
	}

	int dp[500+10][11*11*11*11];
	inline int Solve(int f[4]) {
		int mx = (f[0]-1)*f[1]*f[2]*f[3] + 
				 (f[1]-1)*f[2]*f[3] + 
				 (f[2]-1)*f[3] + 
				 (f[3]-1)*1 + 1;
		for (int i=0; i<o; i++) {
			memset (dp[i], -1, sizeof(int)*mx);
		}
		dp[rt][0] = 0;
		for (int l=0; l<=f[0]+f[1]+f[2]+f[3]-5; l++) {
			for (int a=0; a<f[0]; a++) {
				for (int b=0; b<f[1]; b++) {
					for (int c=0; c<f[2]; c++) {
						int d = l-a-b-c;
						if (d<0 || d>=f[3]) continue;
						int mn = a*f[1]*f[2]*f[3] + 
								b*f[2]*f[3] + 
								c*f[3] + 
								d*1;
						for (int i=0; i<o; i++) {
							if (dp[i][mn] == -1) continue;
							for (int t=0; t<4; t++) {
								if (t==0 && a+1==f[t]) continue;
								if (t==1 && b+1==f[t]) continue;
								if (t==2 && c+1==f[t]) continue;
								if (t==3 && d+1==f[t]) continue;
								int mnx = mn + (
										t==0?f[1]*f[2]*f[3]:
										t==1?f[2]*f[3]:
										t==2?f[3]:1);
								dp[go[i][t]][mnx] = max(dp[go[i][t]][mnx],
										dp[i][mn]+end[go[i][t]]);
							}
						}
					}
				}
			}
		}
		int ret = 0;
		for (int i=0; i<o; i++) {
			ret = max(ret, dp[i][mx-1]);
		}
		return ret;
	}
} ac;

int main () {
	int n;
	char s[50];
	int CASE = 0;
	while (~scanf("%d", &n) && n) {
		ac.Init();
		for (int i=0; i<n; ++i) {
			scanf ("%s", s);
			ac.Ins(s);
		}
		scanf ("%s", s);
		int f[4] = {1,1,1,1};
		for (int i=0; s[i]; ++i) {
			s[i]=='A'?++f[0]:
			s[i]=='G'?++f[1]:
			s[i]=='C'?++f[2]:
					  ++f[3];
		}
		ac.GetFail();
		printf ("Case %d: %d\n", ++CASE, ac.Solve(f));
	}
	return 0;
}
/*
2
TGCG
AT
ATATGCG
*/
