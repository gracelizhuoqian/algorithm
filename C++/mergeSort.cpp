class Solution {
public:
    int InversePairs(vector<int> data) {
        int len=data.size();
        if(!len){
            return 0;
        }
        vector<int> copy(len);
        long long count = mergeSort(data,copy,0,len-1);
        return resize(count);
    }
    int mergeSort(vector<int> &data,vector<int> &copy,int s,int e){
        if(s==e){
            return 0;
        }
        int m=(s+e)/2;
        int count=0;
        count+=mergeSort(data,copy,s,m);
        count=resize(count);
        count+=mergeSort(data,copy,m+1,e);
        count=resize(count);
        int p1=m,p2=e;
        int index=e;
        while(p1>=s&&p2>m){
            if(data[p1]>data[p2]){
                count+=p2-m;
                count=resize(count);
                copy[index--]=data[p1--];
            }else{
                copy[index--]=data[p2--];
            }
        }
        while(p1>=s){
            copy[index--]=data[p1--];
        }
        while(p2>m){
            copy[index--]=data[p2--];
        }
        for(int i=s;i<=e;i++){
            data[i]=copy[i];
        }
        return count;
    }
    int resize(int c){
        return c%1000000007;
    }
};
// 求逆序数对，利用归并排序