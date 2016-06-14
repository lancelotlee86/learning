function prepareSlideshow() {
  // 确保浏览器支持 DOM 方法，并且元素存在
  if (!document.getElementsByTagName) {
    return false;
  }
  if (!document.getElementById) {
    return false;
  }
  if (!document.getElementById("linklist")) {
    return false;
  }
  // 用 javascript 在网页中动态生成可以移动的动画图片的 div，因为没有启用 javascript 的浏览器是不需要这部分元素的
  var slideshow = document.createElement("div");
  slideshow.setAttribute("id", "slideshow");
  var preview = document.createElement("img");
  preview.setAttribute("src", "static/images/topics.gif");
  preview.setAttribute("alt", "building blocks of web design");
  preview.setAttribute("id", "preview");
  slideshow.appendChild(preview);
  var list = document.getElementById("linklist");
  insertAfter(slideshow, list);
  // 取得列表中的所有链接
  var links = list.getElementsByTagName("a");
  // 为 mouseover 事件添加动画效果
  links[0].onmouseover = function() {
    moveElement("preview", -100, 0, 5);
  };
  links[1].onmouseover = function() {
    moveElement("preview", -200, 0, 5);
  };
  links[2].onmouseover = function() {
    moveElement("preview", -300, 0, 5);
  };
}

addLoadEvent(prepareSlideshow);
