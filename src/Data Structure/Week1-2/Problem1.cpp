#include <bits/stdc++.h>
using namespace std;

const int maxn = 10001;
int n,s[maxn],min_v,ans = 0;
pair<int,int> aii;

int main(){
	cin>>n;
	for (int i=1,t;i<=n;i++){
		cin>>t;
		//Calculate the prefix sum
		s[i] = s[i-1] + t;
	}
	
	min_v = 1;
	for (int i=1,t=1;i<=n;i++){
		//Calculate min value of each index
		if (s[i] < s[min_v])
			min_v = i;
			
		if (s[i] - s[min_v] > ans){
			ans = s[i] - s[min_v];
			aii = make_pair(min_v+1,i);
		}
	}
	
	//-1 since our array index begins at 0
	cout<<ans<<' '<<aii.first-1<<'-'<<aii.second-1;
	return 0;
}
