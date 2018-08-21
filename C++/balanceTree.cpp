class Solution {
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
        return getDepth(pRoot)!=-1;
    }
    int getDepth(TreeNode* pRoot){
        if(!pRoot){
            return 0;
        }
        int left=getDepth(pRoot->left);
        if(left==-1){
            return -1;
        }
        int right=getDepth(pRoot->right);
        if(right==-1){
            return -1;
        }
        return abs(left-right)>1?-1:max(left,right)+1;
    }
};

// 注意剪枝，从下向上判断，遇到不平衡子树直接返回