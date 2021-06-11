# 树

### 重建二叉树

输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：[3,9,20,null,null,15,7]
限制：

0 <= 节点个数 <= 5000

```js
const reconstructTree = function (pre, ps, pe, ino, is, ie) {
  // 注意溢出数组
  if (ps > pe || is > ie || pe >= pre.length || ie >= pre.length) {
    return null
  }
  if (ps === pe && is === ie) {
    return new TreeNode(pre[ps])
  }
  let root = new TreeNode(pre[ps])
  let rootIndexOfIn
  // 注意这里ie是索引，因此应该有=判断
  for (let i = is; i <= ie; i++) {
    if (ino[i] === root.val) {
      rootIndexOfIn = i
    }
  }
  let leftSize = rootIndexOfIn - is
  let rightSize = ie - rootIndexOfIn
  root.left = reconstructTree(
    pre,
    ps + 1,
    leftSize + ps,
    ino,
    is,
    rootIndexOfIn - 1
  )
  root.right = reconstructTree(
    pre,
    pe - rightSize + 1,
    pe,
    ino,
    rootIndexOfIn + 1,
    ie
  )
  return root
}
const buildTree = function (preorder, inorder) {
  const len = inorder.length
  return reconstructTree(preorder, 0, len - 1, inorder, 0, len - 1)
}
```
