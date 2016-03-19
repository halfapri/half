#include<bits/stdc++.h>
using namespace std;
int prime[100005],phi[1000005];
int main(){
        int i,j;
        for(i=2;i<1000002;++i){
                if(!phi[i]){
                        phi[i]=i-1;
                        prime[++prime[0]]=i;
                }
                for(j=1;j<=prime[0]&&(long long)i*prime[j]<1000002;++j)
                        if(i%prime[j])phi[i*prime[j]]=phi[i]*(prime[j]-1);
                        else{
                                phi[i*prime[j]]=phi[i]*prime[j];
                                break;
                        }
        }
        int T,n;
        scanf("%d",&T);
        while(T--){
                scanf("%d",&n);
                printf("%d\n",phi[n+1]);
        }
}

