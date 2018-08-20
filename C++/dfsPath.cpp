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
public:
    vector<vector<int> > res;
    vector<int> temp;
    void dfsFind(TreeNode* r,int n){
        temp.push_back(r->val);
        if(!r->right&&!r->left){
            if(r->val==n){
                res.push_back(temp);
            }
        }
        if(r->left){
            dfsFind(r->left,n-r->val);
        }
        if(r->right){
            dfsFind(r->right,n-r->val);
        }
        temp.pop_back();
    }
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        if(root){
            dfsFind(root,expectNumber);
        }
        return res;
    }
};