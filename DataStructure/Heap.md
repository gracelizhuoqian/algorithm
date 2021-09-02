# 堆

## 排序类

### 寻找最小的`k`个数

***(Offer 40)***

#### 思路1. partition

#### 思路2. 大顶堆

先构造一个容量为`k`的大顶堆，每次进来一个元素，与堆顶元素比较。如果小于堆顶，则替换成堆顶元素，然后下沉操作；否则，不做操作。

```js
const sink=(arr,index,k)=>{
  let lastParent=Math.floor((k-2)/2);
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
    // 有右节点，这里注意判断清楚有右节点的情况
    if(rightIndex<=k-1){
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
  // 注意一定要找准最后一个父节点的下标，k表示数量，k-1是最后节点下标
  let lastParent=Math.floor((k-2)/2);
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


### 数据流中的中位数
***(Offer 41)***
#### 思路
考虑查找和插入两个操作的时间复杂度：
1. 无序数组，插入`O(1)`，查找`O(n)`（partition进行查找第`n/2`大的数）
2. 有序数组，插入`O(n)`，查找`O(1)`。
3. 有序链表，插入`O(n)`，查找`O(1)`。
4. 二叉搜索树，插入`O(log n)-O(n)`，查找`O(1)`。AVL，插入`O(log n)`。

中位数是排序之后的中间位置的数或者中间两个数的平均数，中间两个数满足：`p1`是左边的所有数字的最大值，`p2`是右边子数组最小值。可以维护两个堆，插入堆的时间复杂度`O(log n)`，查找`O(1)`。

为了保持两个堆的数量相同，约定奇数次来的数字放在大顶堆，偶数次来的放在小顶堆。设大顶堆堆顶为`m`，小顶堆堆顶为`n`，新来的数字`x`，当`x`是奇数次来的数字时，如果`x<=n`，则直接插入大顶堆，然后取大顶堆堆顶为中位数；如果`x>n`，则和小顶堆堆顶交换，然后把小顶堆堆顶值插入大顶堆，中位数为该值；偶数次类推。

#### 代码

```js
/**
 * initialize your data structure here.
 */
var MedianFinder = function() {
  this.smallHeap=[];
  this.bigHeap=[];
};

const sink=(heap,index,smallOrBig)=>{
  const current=heap[index];
  const length=heap.length;
  while(index<length){
    let leftIndex=index*2+1;
    let rightIndex=index*2+2;
    // 没有子节点
    if(leftIndex>=length){
      break;
    }else if(leftIndex===length-1){
      if((heap[leftIndex]>heap[index]&&smallOrBig===1)||(heap[leftIndex]<heap[index]&&smallOrBig===0)){
        let temp=heap[index];
        heap[index]=heap[leftIndex];
        heap[leftIndex]=temp;
        index=leftIndex;
      }else{
        break;
      }
    }else{
      if((Math.max(heap[leftIndex],heap[rightIndex])>heap[index]&&smallOrBig===1)||(Math.min(heap[leftIndex],heap[rightIndex])<heap[index]&&smallOrBig===0)){
        let minIndex=heap[leftIndex]>heap[rightIndex]?rightIndex:leftIndex;
        let maxIndex=heap[leftIndex]>heap[rightIndex]?leftIndex:rightIndex;
        if(smallOrBig===0){
          let temp=heap[index];
          heap[index]=heap[minIndex];
          heap[minIndex]=temp;
          index=minIndex;
        }else{
          let temp=heap[index];
          heap[index]=heap[maxIndex];
          heap[maxIndex]=temp;
          index=maxIndex;
        }
      }else{
        // 满足条件之后 务必跳出循环！！！
        break;
      }
    }
  }
}

const swim=(heap,index,smallOrBig)=>{
  const current=heap[index];
  const length=heap.length;
  while(index>=0){
    let parent=Math.floor((index-1)/2);
    if(parent<0){
      break;
    }else{
      if((smallOrBig===0&&heap[index]<heap[parent])||(smallOrBig===1&&heap[index]>heap[parent])){
        let temp=heap[index];
        heap[index]=heap[parent];
        heap[parent]=temp;
        index=parent;
      }else{
        break;
      }
    }
  }
}

/**
 * @param {number} num
 * @return {void}
 */
MedianFinder.prototype.addNum = function(num) {
  const smallHeapLength=this.smallHeap.length;
  const bigHeapLength=this.bigHeap.length;
  if(bigHeapLength===0){
    this.bigHeap.push(num);
    return;
  }else if(smallHeapLength===0){
    if(num<this.bigHeap[0]){
      this.smallHeap.push(this.bigHeap[0]);
      this.bigHeap[0]=num;
    }else{
      this.smallHeap.push(num);
    }
    return;
  }
  if(smallHeapLength===bigHeapLength){
    // 奇数次来的放在大顶堆
    const smallTop=this.smallHeap[0];
    if(num>smallTop){
      this.smallHeap[0]=num;
      sink(this.smallHeap,0,0);
      this.bigHeap.push(smallTop);
      swim(this.bigHeap,bigHeapLength,1)
    }else{
      this.bigHeap.push(num);
      swim(this.bigHeap,bigHeapLength,1)
    }
  }else{
    const bigTop=this.bigHeap[0];
    if(num<bigTop){
      this.bigHeap[0]=num;
      sink(this.bigHeap,0,1);
      this.smallHeap.push(bigTop);
      swim(this.smallHeap,smallHeapLength,0)
    }else{
      this.smallHeap.push(num);
      swim(this.smallHeap,smallHeapLength,0)
    }
  }
};

/**
 * @return {number}
 */
MedianFinder.prototype.findMedian = function() {
  const smallHeapLength=this.smallHeap.length;
  const bigHeapLength=this.bigHeap.length;
  const smallTop=this.smallHeap[0];
  const bigTop=this.bigHeap[0];
  if(smallHeapLength===bigHeapLength){
    return (smallTop+bigTop)/2;
  }else{
    return bigTop;
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * var obj = new MedianFinder()
 * obj.addNum(num)
 * var param_2 = obj.findMedian()
 */
```
