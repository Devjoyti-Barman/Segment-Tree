/*

https://codeforces.com/contest/380/problem/C

Here main concept is that

at each index i will have {open,close,correct}

if I know at left and  index how many open and close brackets are there, and I know the ans upto left and right
   then I can say that

  my head index have,
    correct =2*min(left.open,right.close)+left.correct+right.correct;
   
  open=left.open+right.open-min(left.open,right.close);
  lose=left.close+right.close-min(left.open,right.close);


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
string s;
struct Node{
  int open;
  int close;
  int correct;

};


Node tree[4000001];

Node merge(Node left,Node right){
   Node head;
   
   head.correct=2*min(left.open,right.close)+left.correct+right.correct;
   head.open=left.open+right.open-min(left.open,right.close);
  head.close=left.close+right.close-min(left.open,right.close);
  return head;
}
void BuildTree(int index,int ss,int se){
     
     if(ss==se){

         if(s[ss]=='('){
             tree[index].open=1;
             tree[index].close=0;
         }else{
            tree[index].open=0;
            tree[index].close=1;
         }
         tree[index].correct=0;
         return;
     }
     int mid=(ss+se)/2;
     BuildTree(2*index,ss,mid);
     BuildTree(2*index+1,mid+1,se);

     tree[index]=merge(tree[2*index],tree[2*index+1]);
}

Node query(int index,int qs,int qr,int ss,int se){
  if(ss>qr||se<qs)
    return {0,0,0};
  if(ss>=qs and se<=qr) return tree[index];
  int mid=(ss+se)/2;
  return merge(query(2*index,qs,qr,ss,mid),query(2*index+1,qs,qr,mid+1,se));
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
     
  cin>>s;
  int n = (int) s.size()-1;
  BuildTree(1,0,n);
  int q;
  cin>>q;
  while(q--){
    int l,r;
    cin>>l>>r;
    l--;r--;
    cout<<query(1,l,r,0,n).correct<<endl;
  }


     return 0;  
}
