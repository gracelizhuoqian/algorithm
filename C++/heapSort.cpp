class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        if(input.size()<k){
            return {};
        }
        generateHeap(input,k);
        for(int i=k;i<input.size();i++){
            if(input[0]>input[i]){
                input[0]=input[i];
                sortHeap(input,0,k);
            }
        }
        // 务必注意循环变量！！！是否一致
        vector<int> res(input.begin(),input.begin()+k);
        return res;
    }
    void generateHeap(vector<int> &input,int k){
        int noLeaf=k/2-1;
        for(int i=noLeaf;i>=0;i--){
            sortHeap(input,i,k);
        }
    }
    void sortHeap(vector<int> &input,int k, int end){
        int temp = input[k];// 取出当前元素,需要调整到最终的位置
        for(int i=k*2+1;i<end;i=i*2+1){
            if((i+1)<end&&input[i]<input[i+1]){
                i++;
            }// i是子节点中比较大的节点的位置
            if(temp<input[i]){
                input[k]=input[i];
                k=i;//子节点给跑到父节点位置，记录子节点位置，并且temp中保留了被交换的元素
            }else{
                break;
            }
        }
        // 移动过程相当于始终是开始的节点被子节点替换，所以只需要使子节点替换到响应位置，而temp中为当前节点的
        // 值，k中保留了最后一次交换的子节点的位置也就是最终位置
        input[k]=temp;
    }
};