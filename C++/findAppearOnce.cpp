class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        int len=data.size();
        int temper=0;
        for(int i=0;i<len;i++){
            temper^=data[i];
        }
        int flag=1;
        while((temper&flag)==0)flag<<=1;
        // 注意&和==优先级是==更高，这里要找出两个数不同的某一位，通过与运算区分成两个组
        *num1=0;
        *num2=0;
        // 注意指针类型数据，*p表示指向的值
        for(int i=0;i<len;i++){
            if(data[i]&flag){
                *num1^=data[i];
            }else{
                *num2^=data[i];
            }
        }
    }
};
// 利用相同的数可以亦或相消除