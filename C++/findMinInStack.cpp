class Solution {
public:
    stack<int> s;
    stack<int> m;
    void push(int value) {
        if(s.empty()||s.top()>value){
            m.push(value);
        }
        s.push(value);
    }
    void pop() {
        if(!s.empty()){
            if(s.top()==m.top()){
                m.pop();
            }
            s.pop();
        }
    }
    int top() {
        return s.top();
    }
    int min() {
        return m.top();
    }
};
// 在m中每次压栈过程中遇到的比当前栈的最小值还要小的，弹出时要判断是不是最小的被弹出了，如果是要恢复到原先的最小值