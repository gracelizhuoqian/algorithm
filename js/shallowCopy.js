const shallowCopy = function(sobj){
    let robj = null;
    let type = Object.prototype.toString.call(sobj).match(/^\[object (\w+)]$/);
    switch(type){
        case "Array":
            return robj = sobj.slice(0);
        case "Object":
            Object.keys(sobj).forEach((item)=>{
                robj = sobj[item];
            })
            return robj;
        default:
            return robj = sobj;
    } 
}
var key1 = 'name',
    key2 = 13,
    key3 = true,
    key4 = undefined,
    key5 = null,
    key6 = [78,89],
    key7 = {"name":'lzq'};
console.log(shallowCopy(key1));
console.log(shallowCopy(key2));
console.log(shallowCopy(key3));
console.log(shallowCopy(key4));
console.log(shallowCopy(key5));
console.log(shallowCopy(key6));
console.log(shallowCopy(key7));
key7.name="Jolly";
console.log(shallowCopy(key7));
key6.push(12);
console.log(shallowCopy(key6));

