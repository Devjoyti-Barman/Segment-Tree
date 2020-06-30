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

int lazy[100005]={0};

void updateRangeLazy(int *tree,int ss,int se,int l,int r,int inc,int index){
    // Before going down resolve the value if it exists

    if(lazy[index]!=0){

         tree[index]+=lazy[index];
         // non leaf node
         if(ss!=se){
             lazy[2*index]+=lazy[index];
             lazy[2*index+1]+=lazy[index];
         }
         lazy[index]=0; // clear the value
    }

    //no overlap
    if(ss>r or l>se)
      return;

    // Complete Overlap

    if(ss>=l and se<=r){
        tree[index]+=inc;

        // create a new lazy value of childeren node
        if(ss!=se){
            lazy[2*index]+=inc;
            lazy[2*index+1]+=inc;
        }
        return;
    }

    // Partial case

    int mid=(ss+se)/2;
    updateRangeLazy(tree,ss,mid,l,r,inc,2*index);
    updateRangeLazy(tree,mid+1,se,l,r,inc,2*index+1);
    tree[index]=min(tree[2*index],tree[2*index+1]);
}


int queryLazy(int *tree,int ss,int se,int qs,int qe,int index){    
      // Before going down resolve the value if it exists.

    if(lazy[index]!=0){

         tree[index]+=lazy[index];
         // non leaf node
         if(ss!=se){
             lazy[2*index]+=lazy[index];
             lazy[2*index+1]+=lazy[index];
         }
         lazy[index]=0; // clear the value
    }

    // No Overlap
    if(ss>qe or se<qs)
      return INT_MAX;
    // Complte Over lap
    if(ss>=qs and se<=qe){
       return tree[index];
    }

    // Partial Overlap
    int mid=(ss+se)/2;
    int left=queryLazy(tree,ss,mid,qs,qe,2*index);
    int right=queryLazy(tree,mid+1,se,qs,qe,2*index+1);
    return min(left,right);

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


int main()
{
     #ifndef ONLINE_JUDGE
     freopen("input.txt","r",stdin);
     freopen("output.txt","w",stdout);
     #endif
     ios_base::sync_with_stdio(false); 
     cin.tie(nullptr); 
     cout.tie(nullptr);
     
     
    int a[]={1,3,2,-5,6,4};
    int n=sizeof(a)/sizeof(int);

    int size=4*n+1;
    int *tree=new int[size];

    buildTree(a,tree,0,n-1,1);
    
    updateRangeLazy(tree,0,n-1,0,2,10,1);
    updateRangeLazy(tree,0,n-1,0,4,10,1);
    
    cout<<"Q1 1-1 "<<queryLazy(tree,0,n-1,1,1,1)<<endl;

    updateRangeLazy(tree,0,n-1,3,4,10,1);

    cout<<"Q1 3-5 "<<queryLazy(tree,0,n-1,3,5,1);


     return 0;  
}
