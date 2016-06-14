
function addLoadEvent(func) {
  var oldonload = window.onload;
  if (typeof window.onload != 'function') {
    window.onload = func;
  } else {
    window.onload = function() {
      oldonload();
      func(); // 这是作为参数传入的函数
    }
  }
}

function insertAfter( newElement, targetElement) {
  // DOM 只提供了 insertBefore 方法
  var parent = targetElement.parentNode;
  if (parent.lastChild == targetElement) {
    parent.appendChild(newElement);
  } else {
    parent.insertBefore(newElement, targetElement.nextSibling);
    // nextSibling 目标元素的下一个兄弟元素
  }
}

function showPic(whichpic) {
  if (!document.getElementById("placeholder")) {
    // 检测 placeholder 是否存在
    return false;
  }
  var source = whichpic.getAttribute('href');
  var placeholder = document.getElementById('placeholder');
  if (placeholder.nodeName != "IMG") {
    return false;
  }
  placeholder.setAttribute('src', source);
  // placeholder.src = source   is also ok
  if (document.getElementById("description")) {
    // 检测是否存在 description，如不存在则忽略下列代码
    if (whichpic.getAttribute("title")) {
      var text = whichpic.getAttribute('title');
    } else {
      var text = "";
    }
    var description = document.getElementById('description');
    if (description.firstChild.nodeType == 3) {
      description.firstChild.nodeValue = text;
      // description.childNodes[0].nodeValue    is also ok
    }
  }
  return true;
}

function countBodyChildren() {
  var body_element = document.getElementsByTagName('body')[0];
  alert(body_element.childNodes.length);
}

/*
  window.onload = prepareGallery;
  这样也可以，不过适用性不好
*/
// 网页加载完毕时会触发一个 onload 事件
// 必须把 prepareGallery 函数绑定到 onload 事件上
/*
  onload 只能绑定一个指令，可以这样解决
  window.onload = function() {
    firstFunction();
    secondFunction();
  }
  当然更好的办法还是代码中那样
}
*/
function prepareGallery() {
  if (!document.getElementsByTagName || !document.getElementById) {
    // 首先测试该浏览器是否支持这些方法，如不支持则不会执行这些函数
    return false;
  }
  /* the following is another way
  var supported = document.getElementsByTagName && document.getElementById;
  if (!supported) {
    return;
  }
  */
  if (!document.getElementById("imagegallery")) {
    // 第二步，测试该元素是否存在
    return false;
  }
  var gallery = document.getElementById("imagegallery");
  var links = gallery.getElementsByTagName("a");
  for (var i=0; i<links.length; i++) {
    links[i].onclick = function() {
      return !showPic(this)
      /*
      等同于这个
      if (showPic(this)) {
        return false;
      } else {
        return true;
      }
      和这个
      return !showPic(this);
      三元运算符表示的还是清晰一些。
      如果 showPIc 返回 true，我们就返回 false，浏览器就不会打开那链接。
      下面的代码也可以，但是是假设 showPic 函数一定能正常执行，不好。
      showPic(this);
      return false;
      */
    }
    //links[i].onkeypress = links[i].onclick;
    /*
      按下任意按键都可触发 onkeypress
      但最好不用这个，可能导致更多的问题，因为回车键也可以触发 onclick
    */
  }
}

function preparePlaceholder() {
  if (!document.createElement) {
    return false;
  }
  if (!document.createTextNode) {
    return false;
  }
  if (!document.getElementById("imagegallery")) {
    return false;
  }
  var placeholder = document.createElement("img");
  placeholder.setAttribute("id", "placeholder");
  placeholder.setAttribute("src", "images/placeholder.jpg");
  placeholder.setAttribute("alt", "my image gallery");
  var description = document.createElement("p");
  description.setAttribute("id", "description");
  var desctext = document.createTextNode("Choose an image");
  description.appendChild(desctext);
  var gallery = document.getElementById("imagegallery");
  insertAfter(placeholder, gallery);
  insertAfter(description, placeholder);
  /*  有了 insertAfter 方法后，就不用下面这么写的那么费解了
    document.getElementsByTagName("body")[0].appendChild(placeholder);
    document.getElementsByTagName("body")[0].appendChild(description);
  */
}

function insertBeforeTest() {
  // insertBefore usage:
  // parentElement.insertBefore( newElement, targetElement);
  var gallery = document.getElementById("imagegallery");
  var placeholder = document.getElementById("placeholder");
  var description = document.getElementById("description");
  gallery.parentNode.insertBefore(placeholder, gallery);
  gallery.parentNode.insertBefore(description, gallery);
}

function  insertAfterTest() {
  var gallery = document.getElementById("imagegallery");
  var placeholder = document.getElementById("placeholder");
  insertAfter(description, gallery);
}

addLoadEvent(prepareGallery);
addLoadEvent(preparePlaceholder);
// addLoadEvent(insertBeforeTest);
//addLoadEvent(insertAfterTest);
