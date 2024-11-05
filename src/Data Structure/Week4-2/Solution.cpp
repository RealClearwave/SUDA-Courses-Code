#include <iostream>
#include <queue>
using namespace std;

const int maxn = 2007;

struct node{
    int len;
    string val;
    node(){}
    node(string _val){
        val = _val;
        len = val.length();
    }

    bool operator < (const node &a) const{
        return (len > a.len || (len == a.len && val > a.val));
    }
};

priority_queue<node> pq;

long long f[maxn];

string myitoa(int x){
    string ans;
    while (x != 0){
        ans = (char)(48+x%10) + ans;
        x /= 10;
    }
    return ans;
}

long long fastCount(int u){
    if (f[u] != -1) return f[u];
    long long ans = 0;
    for (int i=1;i<=u/2;i++)
        ans += fastCount(i);
    f[u] = ans+1;
    return f[u];
}

void print(int u, string subfix){
    if (pq.size() > 1000) return;
    string curSubfix = myitoa(u) + subfix;
    pq.push(node(curSubfix));
    for (int i=1;i<=u/2;i++)
        print(i, curSubfix);

    return ;
}

int main(){
    int n;cin>>n;
    for (int i=0;i<=n;i++) f[i] = -1;
    long long ans = fastCount(n);
    cout<<"Total="<<ans<<endl;

    print(n,"");
    cout<<"First "<<min(n,1000)<<" numbers:"<<endl;
    while (!pq.empty()){
        cout<<pq.top().val<<' ';
        pq.pop();
    }
    
    return 0;
}