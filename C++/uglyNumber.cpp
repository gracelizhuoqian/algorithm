class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        if(index<7){
            return index;
        }
        vector<int> res(index);
        int index2=0,index3=0,index5=0;
        res[0]=1;
        for(int i=1;i<index;i++){
            res[i]=min(res[index2]*2,res[index3]*3,res[index5]*5);
            if(res[i]==res[index2]*2){index2++;}
            if(res[i]==res[index3]*3){index3++;}
            if(res[i]==res[index5]*5){index5++;}
            
        }
        return res[index-1];
    }
    int min(int a,int b,int c){
        if(a<b){
            return a<c?a:c;
        }else{
            return b<c?b:c;
        }
    }
};
// 三个指针分别指向由*2，*3，*5生成的结果在数组中的数据