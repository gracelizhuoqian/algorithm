class Solution {
public:
    double Power(double base, int exponent) {
        long long temp = abs((long long)exponent);
        double res = 1.0;
        while(temp){
            if(temp&1){
               res*=base; 
            }
            temp=temp>>1;
            base*=base;
        }
        if(exponent<0){
            res=1/res;
        }
        return res;
    }
};
// 运算分解 base^(9)=base^(1001)=base^(1000)*base^(1);
// base^(10)=base^(1)*base;