class Solution {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int temp=n;
        int low=0;
        int location=0;
        int count=0;
        int base=1;
        int high=0;
        int curNum=0;
        while(temp){
            base=pow(10,location);
            // 个位上出现的1，是10的个数*1，
            // 百位上的1，是100的个数*10，有多少个10/100/1000...由高位决定，每个10/100/1000会
            // 分别在个/十/百位上产生1/10/100个1
            high=temp/10; // 有多少个当前位置
            curNum=temp%10; // 当前位置的值
            if(location){
                low=n-temp*pow(10,location); // 低位的值
            }
            if(curNum>1){
                count+=(high+1)*base;
            }else if(curNum==1){
                count+=high*base+low+1;
            }else{
                count+=high*base;
            }
            temp=temp/10;
            location++;
        }
        return count;
    }
};