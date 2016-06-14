function addLoadEvent(func) {
  var oldonload = window.onload;
  if (typeof window.onload != 'function') {
    window.onload = func;
  } else {
    window.onload = function() {
      oldonload();
      func();
    };
  }
}

function insertAfter(newElement,targetElement) {
  var parent = targetElement.parentNode;
  if (parent.lastChild == targetElement) {
    parent.appendChild(newElement);
  } else {
    parent.insertBefore(newElement,targetElement.nextSibling);
  }
}

function addClass(element,value) {
  if (!element.className) {
    element.className = value;
  } else {
    newClassName = element.className;
    newClassName+= " ";
    newClassName+= value;
    element.className = newClassName;
  }
}

function highlightPage() {
  if (!document.getElementsByTagName) {
    return false;
  }
  if (!document.getElementById) {
    return false;
  }
  var headers = document.getElementsByTagName("header");
  if (headers.length == 0) {
    return false;
  }
  var navs = headers[0].getElementsByTagName("nav");
  if (navs.length == 0) {
    return false;
  }
  // 取得导航链接
  var links = navs[0].getElementsByTagName("a");
  var linkurl;
  for (var i = 0; i < links.length; i++) {
      // 遍历导航链接，比较当前链接的 URL 与当前页面的 URL。
      linkurl = links[i].getAttribute("href");
      if (window.location.href.indexOf(linkurl) != -1) {
        // window.location.href 用来表示当前页面的网址，
        // indexOf() 函数返回 -1 时，表示字符串不再里面。
        links[i].className = "here";
      }
  }
}

addLoadEvent(highlightPage);
