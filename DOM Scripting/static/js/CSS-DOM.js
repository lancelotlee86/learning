function styleElementSiblings(tag, theclass) {
  /*
    使用 DOM 脚本设置样式
  */
  if (!document.getElementsByTagName) {
    return false;
  }
  var headers = document.getElementsByTagName(tag);
  var elem;
  for ( var i = 0; i < headers.length; i++) {
    elem = getNextElement(headers[i].nextSibling);
    /*
      直接这样用 javascript 修改属性的方法不太好，
      可以用 javascript 修改标签的 class 属性，
      并将样式放在 css 文件中。
      elem.style.fontWeight = "bold";
      elem.style.fontSize = "1.2em";
    */
    /*
      像这样直接修改 className 属性也可以，但是要注意这是修改，而不是追加，所以应该先判断原来是否已经有了 class 属性
      elem.className = "intro";
    */
    addClass(elem, theclass);
  }
}

function getNextElement(node) {
  if(node.nodeType == 1) {
    return node;
  }
  if (node.nextSibling) {
    return getNextElement(node.nextSibling);
  }
  return null;
}

function addClass(element, value) {
  if (!element.className) {
    element.className = value;
  } else {
    newClassName = element.className;
    newClassName += " ";
    newClassName += value;
    element.className = newClassName; // 注意这里第一个字符是空格
  }
}

addLoadEvent(function() {
  styleElementSiblings("h1", "intro");
})
