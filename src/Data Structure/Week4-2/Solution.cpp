#include <iostream>
using namespace std;

const int maxn = 2007;
long long f[maxn];

long long count(int u){
    if (f[u] != -1) return f[u];
    long long ans = 0;
    for (int i=1;i<=u/2;i++)
        ans += count(i);
    
    f[u] = ans+1;
    return f[u];
}

int main(){
    int n;cin>>n;
    for (int i=0;i<=n;i++) f[i] = -1;
    cout<<count(n);
    return 0;
}