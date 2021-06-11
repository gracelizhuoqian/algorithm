# 链表

```js
const subPrint = (arr, head) => {
  if (!head) {
    return
  }
  subPrint(arr, head.next)
  arr.push(head.val)
}
var reversePrint = function (head) {
  const res = []
  subPrint(res, head)
  return res
}
```
