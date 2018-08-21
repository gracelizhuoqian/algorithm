class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        int len=numbers.size();
        if(!len){
            return 0;
        }
        int ans=numbers[0];
        int times=1;
        for(int i=1;i<len;i++){
            if(times==0){
                ans=numbers[i];
                times=1;
            }else if(numbers[i]==ans){
                times++;
            }else{
                times--;
            }
        }
        if(times==0){
            return 0;
        }
        times=0;
        for(int i=0;i<len;i++){
            if(numbers[i]==ans){
                times++;
            }
        }
        return (times>len/2)?ans:0;
    }
};
// 结果数字出现的次数要大于其他所有数字出现的次数之和，每次出现和不出现都可以相互抵消直到最后还出现