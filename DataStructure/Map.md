# 图

## DFS

**_ 04.01 _**

#### 代码

```js
/**
 * @param {number} n
 * @param {number[][]} graph
 * @param {number} start
 * @param {number} target
 * @return {boolean}
 */
var findWhetherExistsPath = function (n, graph, start, target) {
  const graphArray = [];
  const visited = [];
  for (let i = 0; i < n; i++) {
    graphArray[i] = [];
    visited[i] = false;
  }
  for (let i = 0; i < graph.length; i++) {
    let num1 = graph[i][0];
    let num2 = graph[i][1];
    graphArray[num1].push(num2);
  }
  return DFS(graphArray, visited, start, target);
};
const DFS = (graph, visited, start, target) => {
  if (start === target) {
    return true;
  }
  visited[start] = true;
  for (let i = 0; i < graph[start].length; i++) {
    if (!visited[graph[start]]) {
      let temp = DFS(graph, visited, graph[start][i], target);
      if (temp === true) {
        return true;
      }
    }
  }
  return false;
};
```
