/*

https://hack.codingblocks.com/app/practice/2/302/problem
*/



#include<bits/stdc++.h>
using namespace std;
#define w(t) int t;cin>>t;while(t--)
#define pb   push_back
#define mk   make_pair
#define u_s  unordered_set 
#define prDouble(x) cout<<fixed<<setprecision(10)<<x
typedef long long int ll;
typedef pair<int,int>ipair;
const ll mod=1e9+7;
bool compare(pair<int,int>p1,pair<int,int>p2){
    return p1.second<p2.first;
}

void buildTree(int *a,int *tree,int ss,int se,int index){

        if(ss==se){
            tree[index]=a[ss];
            return;
        }

        int m=(ss+se)/2;

        buildTree(a,tree,ss,m,2*index);
        buildTree(a,tree,m+1,se,2*index+1);
        tree[index]=min(tree[2*index],tree[2*index+1]);
}

int query(int *tree,int ss,int se,int qs,int qe,int index){
  //Complete Overlap
  if(ss>=qs and se<=qe)return tree[index];
  // No Overlap
  if(qe<ss or qs>se)return INT_MAX;
  // Partial Overlap
  int mid=(ss+se)/2;
  int left=query(tree,ss,mid,qs,qe,2*index);
  int right=query(tree,mid+1,se,qs,qe,2*index+1);
  return min(left,right);
} 
void update(int *tree,int s,int e,int i,int inc,int index){
    // case where ind out of bound

    if(i>e or i<s)return;

    // leaf node
    if(s==e){
        tree[index]=inc;
        return;
    }
    // Otherwise
    int mid=(s+e)/2;
    update(tree,s,mid,i,inc,2*index);
    update(tree,mid+1,e,i,inc,2*index+1);
    tree[index]=min(tree[2*index],tree[2*index+1]);
}

int main()
{

     ios_base::sync_with_stdio(false); 
     cin.tie(nullptr); 
     cout.tie(nullptr);
     
     
    int n,q;cin>>n>>q;
    int a[n];for(int i=0;i<n;i++)cin>>a[i];

    int size=4*n+1;
    int *tree=new int[size];

    buildTree(a,tree,0,n-1,1);
    
    while(q--){

        int k,x,y;
        cin>>k>>x>>y;

        if(k==1){
            cout<<query(tree,0,n-1,x-1,y-1,1)<<endl;
        }else{
            update(tree,0,n-1,x-1,y,1);
        }
    }
    

     return 0;  
}
