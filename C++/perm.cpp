class Solution {
public:
    vector<string> ans;
    vector<string> Permutation(string str) {
        int len=str.length();
        if(!len){
            return ans;
        }
        perm(0,str);
        sort(ans.begin(),ans.end());
        return ans;
    }
    void perm(int k,string str){
        int len=str.length();
        if(k==len-1){
            ans.push_back(str);
            return;
        }
        for(int i=k;i<len;i++){
            if(i!=k && str[i]==str[k]){
                continue;
            }
            swap(str[i],str[k]);
            perm(k+1,str);
            swap(str[i],str[k]);
        }
    }
};
// 全排列，需要记录当前交换的位置，将后面的部分依次根当前位置交换，当位置为末尾时，将当前字符串压入结果