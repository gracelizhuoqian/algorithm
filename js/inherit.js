// 原型链继承
function Parent(name){
    this.name=name;
}
Parent.prototype.getName=function(){
    return this.name;
}
function Child(age){
    this.age=age;
}
Child.prototype=new Parent('Jolly');

// 构造函数继承
function Parent(name){
    this.name=name;
}
function Child(age){
    this.super()
}

// 缺点：1.父类的实例属性，被所有子类的实例共享