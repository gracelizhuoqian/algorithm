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
// 类似：连续子数组的最大和，如果有正有负，那么设置变量保存最大和，一旦一段里面的和小于零，这段就不再有价值，因为如果这一段前面有正的值，那么合起来就不会小于零，也就意味着前面的都没有价值，只需要从后面开始重新考虑
class Solution {
public: 
    int FindGreatestSumOfSubArray(vector<int> array) {
        int max=0;
        int sum=0;
        int len=array.size();
        for(int i=0;i<len;i++){
            if(sum<=0){
                sum=array[i];
            }else{
                sum+=array[i];
            }
            if(sum>max){
                max=sum;
            }
        }
        if(max==0&&start==len-1){
            max=array[0];
            for(int i=0;i<len;i++){
                if(array[i]>max){
                    max=array[i];
                }
            }
        }
        return max;
    }
};