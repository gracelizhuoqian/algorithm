class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        int len=A.size();
        vector<int> B(len,1),temp(len,1);
        if(!len){
            return B;
        }
        for(int i=1;i<len;i++){
            B[i]=B[i-1]*A[i-1];
        }
        for(int j=len-2;j>=0;j--){
            temp[j]=A[j+1]*temp[j+1];
        }
        for(int i=0;i<len;i++){
            B[i]=B[i]*temp[i];
        }
        return B;
    }
};
// 杨辉三角，B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]。其中，可以先讲求一个三角的值，再求另一个三角的值，再对应相乘