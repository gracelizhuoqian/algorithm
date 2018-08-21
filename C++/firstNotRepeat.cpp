class Solution {
    int buf[100];
    // 呵呵哒，小写字母和大写字母的ASCLL不是连着的。。。
public:
    int FirstNotRepeatingChar(string str) {
        int index=0;
        int len=str.length();
        if(!len){
            return -1;
        }
        for(int i=0;i<100;i++){
            buf[i]=0;
        }
        buf[str[0]-65]++;
        for(int i=1;i<len;i++){
            buf[str[i]-65]++;
            if(str[index]==str[i]){
                while(index<=i){
                    if(buf[str[index]-65]>1){
                        index++;
                    }else{
                        break;
                    }
                }
            }
        }
        return index;
    }
};
// 用一个指针指向当前第一个只出现一次的字母，如果遇到新字母和标志位的字母一致，需要更新标志位，每个字母出现的次数要存起来，用hash思想