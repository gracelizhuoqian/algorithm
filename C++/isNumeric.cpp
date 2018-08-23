class Solution {
public:
    bool isNumeric(char* string)
    {
        bool hasE=false,dot=false,sign=false;
        // 标志位保存方式
        int len=strlen(string);
        if(!len){
            return false;
        }
        for(int i=0;i<len;i++){
            if(string[i]=='E'||string[i]=='e'){
                if(hasE||i==len-1)return false;
                hasE=true;
            }else if(string[i]=='.'){
                if(dot||hasE)return false;
                dot=true;
            }else if(string[i]=='+'||string[i]=='-'){
                if(sign){
                    if(string[i-1]!='e'&&string[i-1]!='E')return false;
                }else{
                    if(i!=0&&(string[i-1]!='E'&&string[i-1]!='e'))return false;
                    sign=true;
                }
            }else if(string[i]<'0'||string[i]>'9'){
                return false;
            }
        }
        return true;   
    }

};