#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

typedef complex<double> Complex;
const double pi = acos(-1.0);
const double eps = 1e-6;

inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = (100000+10)<<2;
Complex x1[M], x2[M];
int a[M];
ll sum[M];
ll re[M];
ll suff[M];
int l;
int n;

void fft(Complex *a, int n, int rev) {
    // n是大于等于相乘的两个数组长度的2的幂次
    // 从0开始表示长度，对a进行操作
    // rev==1进行DFT，==-1进行IDFT
    for (int i = 1,j = 0; i < n; ++ i) {
        for (int k = n>>1; k > (j^=k); k >>= 1);
        if (i<j) std::swap(a[i],a[j]);
    }
    for (int m = 2; m <= n; m <<= 1) {
        Complex wm(cos(2*pi*rev/m),sin(2*pi*rev/m));
        for (int i = 0; i < n; i += m) {
            Complex w(1.0,0.0);
            for (int j = i; j < i+m/2; ++ j) {
                Complex t = w*a[j+m/2];
                a[j+m/2] = a[j] - t;
                a[j] = a[j] + t;
                w = w * wm;
            }
        }
    }
    if (rev==-1) {
        for (int i = 0; i < n; ++ i) a[i] /= n;
    }
}

int main()
{
	int CASE;
	scanf ("%d", &CASE);
	while (CASE --) {
		scanf ("%d", &n);
		for (int i=0; i<n; ++i) {
			scanf ("%d", a+i);
		}
		sort (a, a+n);
		int len = a[n-1]+1;
		l = 1;
		while (l < 2*len) l<<=1;
		memset (sum, 0, sizeof(sum[0])*(l+1));
		for (int i=0; i<n; ++i) {
			++ sum[a[i]];
		}
		for (int i=0; i<l; ++i) {
			x1[i] = Complex(1.0*sum[i], 0.0);
		}
		//for (int i=0; i<len; ++i) {
		//	printf ("sum[%d]=%d\n", i, sum[i]);
		//}
		fft (x1, l, 1);
		for (int i=0; i<l; ++i) {
			x1[i] = x1[i] * x1[i];
		}
		fft (x1, l, -1);
		for (int i=0; i<l; ++i) {
			re[i] = ll(x1[i].real() + eps);
		}
		for (int i=0; i<n; ++i) {
			--re[a[i]+a[i]];
		}
		for (int i=0; i<l; ++i) {
			re[i] /= 2;
			//printf ("re[%d]="LLD"\n", i, re[i]);
		}
		memset (suff, 0, sizeof(suff[0])*(l+1));
		for (int i=l-1; i>=0; --i) {
			suff[i] = suff[i+1] + sum[i];
		}
		ll tot = 1ll*n*(n-1)*(n-2)/6;
		ll f = tot;
		for (int i=2; i<l; ++i) {
			f -= 1ll*re[i]*suff[i];
			//printf ("re[%d]="LLD",suff[%d]="LLD"\n",
					//i,re[i],i,suff[i]);
		}
		printf ("%.7f\n", f/(1.0*tot));
	}
	return 0;
}
