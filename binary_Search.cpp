#include<bits/stdc++.h>
using namespace std;
int BinarySearch(int target,int n,int arr[])
{
    int low=0;
    int high=n-1;
    int mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(arr[mid]==target) return mid;
        if(target<arr[mid])
            high=mid-1;
        else if(target>arr[mid])
            low=mid+1;
    }
    return -1;
}
int main()
{
    int arr[]={1,2,4,6,8,9,10};
    int n=sizeof(arr)/sizeof(arr[0]);
    int found=BinarySearch(4,n,arr);
    cout<<"Found at: "<<found;
    return 0;
}