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
    ListNode* ReverseList(ListNode* pHead) {
        if(!pHead){
            return NULL;
        }
        ListNode* pre=NULL;
        ListNode* next=NULL;
        ListNode* cur=pHead;
        while(cur){
            next=cur->next;
            cur->next=pre;
            pre=cur;
            cur=next;
        }
        return pre;
    }
};
// 思路，循环对当先节点的next指针进行反转，为了保证不断链接需要保存当前节点的下一个节点