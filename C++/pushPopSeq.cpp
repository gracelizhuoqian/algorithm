class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        stack<int> s;
        if(!pushV.size()||pushV.size()!=popV.size()){
            return false;
        }
        int pushIndex=0;
        for(int i=0;i<popV.size();i++){
            while(s.empty()||popV[i]!=s.top()){
                if(pushIndex==pushV.size()){
                    return false;
                }
                s.push(pushV[pushIndex++]);
            }
            if(popV[i]==s.top()){
                s.pop();
                continue;
            }
        }
        return true;
    }
};
// pushIndex记录压栈数组的访问顺序，当压栈的元素越界时，则说明错误