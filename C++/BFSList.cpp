/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
    TreeNode* head=NULL;
    TreeNode* tail=NULL;
public:
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if(!pRootOfTree){
            return NULL;
        }
        Convert(pRootOfTree->left);
        // 不需要返回值的时候，需要每次在全局变量上操作
        if(!head){
            // 第一次进来的一定是最左边的节点
            head=tail=pRootOfTree;
        }else{
            tail->right=pRootOfTree;
            pRootOfTree->left=tail;
            tail=pRootOfTree;
        }
        // 链表头部保持，尾部随每次添加而移动
        Convert(pRootOfTree->right);
        return head;
    }
};