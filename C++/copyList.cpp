/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
/*
输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），返回结果为复制后复杂链表的head。
*/
// 思路：每个节点后复制一个节点，串联成一个新的链表，改变每个新节点的random指向，再把应该返回的链表剥离出来
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(!pHead){
            return NULL;
        }
        RandomListNode* p=pHead;
        while(p){
            RandomListNode* s=new RandomListNode(p->label);
            s->next=p->next;
            p->next=s;
            p=s->next;
        }
        // 这里务必注意，如果跳到了p的值为空，那么判断p->next就会报错，所以判断时要格外小心，保证不会直接跳到空才能在循环中判断p->next
        p=pHead;
        while(p){
            if(p->random){
                p->next->random=p->random->next;
            }
            p=p->next->next;
        }
        RandomListNode* res=pHead->next;
        p=pHead;
        RandomListNode* temp=NULL;
        while(p->next){
            temp=p->next;
            p->next=temp->next;
            p=temp;
        }
        return res;
    }
};