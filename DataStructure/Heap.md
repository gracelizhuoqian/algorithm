# 堆

## 排序类

### 寻找最小的`k`个数

***(Offer 40)***

#### 思路1. partition

#### 思路2. 大顶堆

先构造一个容量为`k`的大顶堆，每次进来一个元素，与堆顶元素比较。如果小于堆顶，则替换成堆顶元素，然后下沉操作；否则，不做操作。

```js
const sink=(arr,index,k)=>{
  let lastParent=Math.floor((k-1)/2);
  let cur=index;
  while(cur<=lastParent){
    let leftIndex=cur*2+1;
    let rightIndex=cur*2+2;
    let maxValue;
    let curNode=cur;
    // 必须选大的换上去，否则两个子节点可能都有变更
    // 没有右节点
    if(leftIndex===k-1&&arr[leftIndex]>arr[cur]){
      maxValue=arr[leftIndex];
      arr[leftIndex]=arr[cur];
      arr[cur]=maxValue;
      curNode=leftIndex;
    }
    // 有右节点
    if(rightIndex<k-1){
      maxValue=Math.max(arr[rightIndex],arr[leftIndex],arr[cur]);
      if(maxValue===arr[cur]){
        break;
      }else if(maxValue===arr[rightIndex]){
        arr[rightIndex]=arr[cur];
        arr[cur]=maxValue;
        curNode=rightIndex;
      }else{
        arr[leftIndex]=arr[cur];
        arr[cur]=maxValue;
        curNode=leftIndex;
      }
    }
    // 没有变更
    if(cur===curNode){
      break;
    }
    cur=curNode;
  }
}
const buildHeap=(arr,k)=>{
  let lastParent=Math.floor((k-1)/2);
  for(let i=lastParent;i>=0;i--){
    sink(arr,i,k);
  }
}

const findMaxK=(arr,k)=>{
  buildHeap(arr,k);
  for(let i=k;i<arr.length;i++){
    if(arr[0]>arr[i]){
      arr[0]=arr[i];
      sink(arr,0,k);
    }
  }
  return arr.slice(0,k);
}
```
