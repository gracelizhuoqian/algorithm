# singleton--单例模式

## background

定义：一个只有一个实例的类  
应用：缓存池，全局变量，window 对象等，在全局中只需要有一个  
要点：

1. 单一职责，每个函数实现一个主要功能，因此需要两个函数，一个构造函数，一个控制单例
2. 具有通用可扩展性，遇到下一个单例，可以不用复制代码

## instance

### 代理模式

分离的两个函数

```js
// 构造函数
const ConstructorExp = function(name){
  this.name = name
}
// 代理类，注意返回的是一个函数，闭包是为了封装状态变量
const proxySingleton = (() => {
  // 可以用闭包或者用this绑定到类上
  let instance
  return (arguments) => {
    if (!instance) {
      instance = new ConstructorExp(arguments)
    }
    return instance
  }
})()

proxySingleton('jolly');
// ConstructorExp {name: "jolly"}
proxySingleton('test');
// ConstructorExp {name: "jolly"}
```

### 通用惰性单例

实现单例的作为一个工厂函数，将构造函数作为参数

```js
// 调用getSingleton()会返回一个实现了单例的构造
const getSingleton =function (constructorFn) {
  let instance
  return function() {
      if(!instance){
          instance = new constructorFn(arguments)
      }
    return instance
  }
}
const ConstructorExp = function(arguments){
  this.name = arguments[0];
}
const singletonDemo = getSingleton(ConstructorExp)
singletonDemo('jolly')
// ConstructorExp {name: "jolly"}
singletonDemo('test')
// ConstructorExp {name: "jolly"}
```
