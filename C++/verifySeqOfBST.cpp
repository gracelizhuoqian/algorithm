// 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
// 利用二叉树的特性，找到根，构建出左子树右子树，再判断是否符合搜索二叉树
class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.empty()){
            return false;
        }
        return isSubBST(sequence,0,sequence.size()-1);
    }
    bool isSubBST(vector<int> s,int start,int end){
        if(start>=end){
            return true;
        }
        int flag=-1;
        for(int i=start;i<end;i++){
            if(s[i]>s[end]){
                flag=i;
                break;
            }
        }
        // 没有右子树，flag==-1
        if(flag==-1){
            return isSubBST(s,start,end-1);
        }
        // 没有左子树
        for(int j=flag;j<end;j++){
            if(s[j]<s[end]){
                return false;
            }
        }
        if(flag==start){
            return isSubBST(s,start,end-1);
        }else{
            return isSubBST(s,start,flag-1)&&isSubBST(s,flag,end-1);
        }
    }
};