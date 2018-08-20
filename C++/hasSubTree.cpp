/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
    //注意不是相等而是包含关系，包含是对值的判断
class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(!pRoot2){
            return false;
        }
        if(pRoot1){
            // 注意在这里对非空的判断
            bool res=false;
            if(pRoot1->val==pRoot2->val){
                res=isSame(pRoot1,pRoot2);
            }
            if(!res){
                res=HasSubtree(pRoot1->left,pRoot2)||HasSubtree(pRoot1->right,pRoot2);
            }
            return res;
        }else{
            return false;
        }
    }
    bool isSame(TreeNode* p1,TreeNode* p2){
        if(!p2){
            return true;
        }
        if(!p1||p1->val!=p2->val){
            return false;
        }
        return isSame(p1->left,p2->left)&&isSame(p1->right,p2->right);
    }
};
