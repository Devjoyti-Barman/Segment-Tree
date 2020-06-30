/*
problem:https://hack.codingblocks.com/app/practice/2/689/problem
solution:https://www.geeksforgeeks.org/maximum-subarray-sum-given-range/
*/
#include<bits/stdc++.h>
using namespace std;
#define w(t) int t;cin>>t;while(t--)
#define pb   push_back
#define mk   make_pair
#define u_s  unordered_set 
#define prDouble(x) cout<<fixed<<setprecision(10)<<x
#define inf 0x3f3f 
typedef long long int ll;
typedef pair<int,int>ipair;
const ll mod=1e9+7;
bool compare(pair<int,int>p1,pair<int,int>p2){
    return p1.second<p2.first;
}

struct Node { 
  int maxPrefixSum; 
  int maxSuffixSum; 
  int totalSum; 
  int maxSubarraySum; 

  Node() 
  { 
    maxPrefixSum = maxSuffixSum = maxSubarraySum = -inf; 
    totalSum = -inf; 
  } 
}; 

Node merge(Node leftChild, Node rightChild) 
{ 
  Node parentNode; 
  parentNode.maxPrefixSum = max(leftChild.maxPrefixSum, 
                leftChild.totalSum + 
                rightChild.maxPrefixSum); 

  parentNode.maxSuffixSum = max(rightChild.maxSuffixSum, 
                rightChild.totalSum + 
                leftChild.maxSuffixSum); 

  parentNode.totalSum = leftChild.totalSum + 
            rightChild.totalSum; 

  parentNode.maxSubarraySum = max({leftChild.maxSubarraySum, 
                  rightChild.maxSubarraySum, 
                  leftChild.maxSuffixSum + 
                  rightChild.maxPrefixSum}); 

  return parentNode; 
} 

void BuildTree(Node* tree, int *arr, int start, 
                  int end, int index) 
{ 

  /* Leaf Node */
  if (start == end) { 

    // single element is covered under this range 
    tree[index].totalSum = arr[start]; 
    tree[index].maxSuffixSum = arr[start]; 
    tree[index].maxPrefixSum = arr[start]; 
    tree[index].maxSubarraySum = arr[start]; 
    return; 
  } 

  // Recursively Build left and right children 
  int mid = (start + end) / 2; 
  BuildTree(tree, arr, start, mid, 2 * index); 
  BuildTree(tree, arr, mid + 1, end, 2 * index + 1); 

  // Merge left and right child into the Parent Node 
  tree[index] = merge(tree[2 * index], tree[2 * index + 1]); 
} 

Node query(Node* tree, int ss, int se, int qs, 
              int qe, int index) 
{ 
  // No overlap 
  if (ss > qe || se < qs) { 

    // returns a Node for out of bounds condition 
    Node nullNode; 
    return nullNode; 
  } 

  // Complete overlap 
  if (ss >= qs && se <= qe) { 
    return tree[index]; 
  } 

  // Partial Overlap Merge results of Left 
  // and Right subtrees 
  int mid = (ss + se) / 2; 
  Node left = query(tree, ss, mid, qs, qe, 
                  2 * index); 
  Node right = query(tree, mid + 1, se, qs, 
              qe, 2 * index + 1); 

  // merge left and right subtree query results 
  Node res = merge(left, right); 
  return res; 
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
     
    int n;cin>>n;
    int a[n];
    for(int i=0;i<n;i++)cin>>a[i]; 
   
    int size=4*n+1;
    Node tree[size];
    BuildTree(tree,a,0,n-1,1);

    int q;cin>>q;
    while(q--){
         int l,r;cin>>l>>r;
         cout<<query(tree,0,n-1,l-1,r-1,1).maxSubarraySum<<endl;
    }     
return 0;  
    
}
