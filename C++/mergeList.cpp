/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if((!pHead1)&&(!pHead2)){
            return NULL;
        }
        if(!pHead1||!pHead2){
            return pHead1?pHead1:pHead2;
        }
        if(pHead1->val>=pHead2->val){
            pHead2->next=Merge(pHead1,pHead2->next);
            return pHead2;
        }else{
            pHead1->next=Merge(pHead1->next,pHead2);
            return pHead1;
        };
    }
};
// 递归合并