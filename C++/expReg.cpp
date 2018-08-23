class Solution {
public:
    bool match(char* str, char* pattern)
    {
        if(!str||!pattern){
            return false;
        }
        return subMatch(str,pattern);
    }
    bool subMatch(char* str,char* pattern){
        if((*str=='\0')&&(*pattern=='\0')){
            return true;
        }
        if((*str!='\0')&&(*pattern=='\0')){
            return false;
        }
        char* sIdx=str;
        char* pIdx=pattern;
        if(*(pIdx+1)=='*'){
            if(*pIdx=='.'&&*sIdx!='\0'||*pIdx==*sIdx){
                return subMatch(sIdx,pIdx+2)||subMatch(sIdx+1,pIdx+2)||subMatch(sIdx+1,pIdx);
            }else{
                return subMatch(sIdx,pIdx+2);
            }
        }else{
            if(*pIdx=='.'&&*sIdx!='\0'||*pIdx==*sIdx){
                return subMatch(sIdx+1,pIdx+1);
            }else{
                return false;
            }
        }
    }
};
/*
模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式
*/