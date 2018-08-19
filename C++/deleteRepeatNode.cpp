/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
// 思路：快慢指针，快指针判断重复，慢指针维持连接
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if(!pHead || !pHead->next){
            return pHead;
        }
        ListNode* h=new ListNode(-1);// 指针必需先分配空间初始化
        ListNode* start;
        ListNode* end;
        h->next = pHead;
        start=h;
        end=pHead;
        while(end&&end->next){
            bool flag = false;//当前没有重复
            while(end->next&&end->val==end->next->val){
                end=end->next;
                flag = true;
            }
            if(flag==true){
                start->next=end->next;
                end=end->next;
            }else{
                end=end->next;
                start=start->next;
            }
        }
        return h->next;
    }
};
