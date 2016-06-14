function getElementsByClassName(node, classname) {
  // 用于有些不支持 getElementsByClassName 的 Javascript 引擎，并使其支持
  if(node.getElementsByClassName) {
    // 使用现有方法
    return node.getElementsByClassName(classname);
  } else {
    var results = new Array();
    var elems = node.getElementsByTagName('*');
    for(var i=0; i<elems.length; i++) {
      if(elems[i].className.indexOf(classname) != -1) {
        // indexOf() 方法可返回某个指定的字符串值在字符串中首次出现的位置。
        // 未出现则返回 -1
        results[result.length] = elems[i];
      }
    }
    return results;
  }
}

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

function displayAbbreviations() {
  /*
    把文档里的缩略语显示为一个 “缩略语列表”
  */
  if (!document.getElementsByTagName || !document.createElement || !document.createTextNode) {
    // 检测是否支持我们使用的这些方法
    return false;
  }
  // 取得所有的缩略词
  var abbreviations = document.getElementsByTagName("abbr");
  if (abbreviations.length < 1) {
    // 如果没有缩略语 abbr 标签
    return false;
  }
  var defs = new Array();
  // 遍历所有的缩略词
  for (var i=0; i<abbreviations.length; i++) {
    /*
      将 abbr 标签中文本节点的内容作为 key，
      将 abbr 标签中 title 属性的值作为 value，
      构建 defs 数组的键值对。
    */
    var current_abbr = abbreviations[i];
    if (current_abbr.childNodes.length < 1) {
      continue;
    }
    var definition = current_abbr.getAttribute("title");
    var key = current_abbr.lastChild.nodeValue;
    defs[key] = definition;
  }
  // 创建定义表 dlist，即 <dl>
  var dlist = document.createElement("dl");
  // 遍历定义
  for (key in defs) {
    var definition = defs[key];
    // 创建定义标题 dtitle 即 <dt>
    var dtitle = document.createElement("dt");
    var dtitle_text = document.createTextNode(key);
    dtitle.appendChild(dtitle_text);
    // 创建定义描述 ddesc, 即 <dd>
    var ddesc = document.createElement("dd");
    var ddesc_text = document.createTextNode(definition);
    ddesc.appendChild(ddesc_text);
    // 添加包含着文本节点 dtitle_text 和 ddesc_text 的 两个元素节点 dtitle 和 ddesc 到 dlist
    dlist.appendChild(dtitle);
    dlist.appendChild(ddesc);
  }
  // 创建标题
  if (dlist.childNodes.length < 1) {
    return false;
  }
  var header = document.createElement("h2");
  var header_text = document.createTextNode("Abbreviations");
  header.appendChild(header_text);
  // 把标题和定义列表添加到页面主体
  document.body.appendChild(header);
  document.body.appendChild(dlist);
}

function displayCitations() {
  /*
    为文档里引用的每段文献节选生成一个 “文献来源链接”
  */
    // 将所有的 blockquote 元素中的 cite 属性的值取出来，
    // 作为链接放在引用的文字段之后。
  var quotes = document.getElementsByTagName("blockquote");
  for (var i = 0; i < quotes.length; i++) {
    // 准备创建链接所需要的东西
    if (!quotes[i].getAttribute("cite")) {
      continue;
    }
    var url = quotes[i].getAttribute("cite"); // url 包含 blockquote 中 cite 的值
    var quoteChildren = quotes[i].getElementsByTagName("*");
    if (quoteChildren.length < 1) {
      continue;
    }
    // 取得引用中最后一个元素节点
    var elem = quoteChildren[quoteChildren.length - 1];  // elem 包含着链接插入位置的节点
    // 创建链接
    var link = document.createElement("a");
    var link_text = document.createTextNode("source");
    link.appendChild(link_text);
    link.setAttribute("href", url);
    // 插入链接
    var superscript = document.createElement("sup");
    superscript.appendChild(link);
    // 把标记添加到引用中的最后一个元素节点
    elem.appendChild(superscript);
  }
}

function displayAccesskeys() {
  /*
    把文档所支持的快捷键显示为一份 “快捷键清单”
  */
  if (!document.getElementsByTagName || !document.createElement || !document.createTextNode) {
    return false;
  }
  // 取得文档中所有链接
  var b = 2;
  var links = document.getElementsByTagName("a");
  // 创建一个数组，保存访问键
  var akeys = new Array();
  // 遍历链接
  for ( var i = 0; i < links.length; i++) {
    var current_link = links[i];
    // 如果没有 accesskey 属性，继续循环
    if (!current_link.getAttribute("accesskey")) {
      continue;
    }
    // 取得 accesskey 和链接文本的值并出入数组
    var key = current_link.getAttribute("accesskey");
    var text = current_link.lastChild.nodeValue;
    akeys[key] = text;
  }
  // 创建列表
  var list = document.createElement("ul");
  for ( key in akeys) {
    var text = akeys[key];
    var str = key + ": " + text;
    var item = document.createElement("li");
    var item_text = document.createTextNode(str);
    item.appendChild(item_text);
    list.appendChild(item);
  }
  // 创建标题
  var header = document.createElement("h3");
  var header_text = document.createTextNode("Accesskeys");
  header.appendChild(header_text);
  // 添加标题和列表到页面
  document.body.appendChild(header);
  document.body.appendChild(list);
}

function stripeTables() {
  /*
    为表格添加斑马线效果
  */
  if (!document.getElementsByTagName) {
    return false;
  }
  var tables = document.getElementsByTagName("table");
  var odd, rows;
  for (var i = 0; i < tables.length; i++) {
    odd = false;
    rows = tables[i].getElementsByTagName("tr");
    for (var j = 0; j < rows.length; j++) {
      if (odd == true) {
        rows[j].style.backgroundColor = "#ffc";
        odd = false;
      } else {
        odd = true;
      }
    }
  }
}

function highlightRows() {
  /*
    当鼠标悬停在某个表格行的上方时，把该行文本加黑加粗
  */
  if (!document.getElementsByTagName) {
    return false;
  }
  var rows = document.getElementsByTagName("tr");
  for (var i = 0; i < rows.length; i++) {
    rows[i].onmouseover = function() {
      this.style.fontWeight = "bold";
    }
    rows[i].onmouseout = function() {
      this.style.fontWeight = "normal";
    }
  }
}

function addClass(element, value) {
  /*
    判断 element 元素有没有 class 属性，
    如果没有则直接赋值，如果有则追加。
  */
  if (!element.className) {
    element.className = value;
  } else {
    newClassName = element.className;
    newClassName += " ";
    newClassName += value;
    element.className = newClassName; // 注意这里第一个字符是空格
  }
}

function moveElement(elementID, final_x, final_y, interval) {
  /*
    移动 id 为 elementID 的元素，以时间间隔为 interval，向着横纵坐标为 final_x 和 final_y 靠近1个像素
  */
  if (!document.getElementById) {
    return false;
  }
  if (!document.getElementById(elementID)) {
    return false;
  }
  // 取得要移动的元素的对象
  var elem = document.getElementById(elementID);
  if (elem.movement) {
    // 用属性来表示 只与某个特定元素有关的变量，这里用全局变量和局部变量都不行
    clearTimeout(elem.movement);
  }
  // 获取元素当前位置
  if (!elem.style.left) {
    elem.style.left = "0px";
  }
  if (!elem.style.top) {
    elem.style.top = "0px"
  }
  var xpos = parseInt(elem.style.left);
  var ypos = parseInt(elem.style.top);
  var dist = 0;
  // 如果元素已经到达它的目的地，则退出这个函数
  if (xpos == final_x && ypos == final_y) {
    return true;
  }
  // 如果元素还没有到目的地，则将其坐标设置的更靠近一个像素
  if (xpos < final_x) {
    dist = Math.ceil((final_x - xpos)/10);
    xpos = xpos + dist;
  }
  if (xpos > final_x) {
    dist = Math.ceil((xpos - final_x)/10);
    xpos = xpos - dist;
  }
  if (ypos < final_y) {
    dist = Math.ceil((final_y - ypos)/10);
    ypos = ypos + dist;
  }
  if (ypos > final_y) {
    dist = Math.ceil((final_y - ypos)/10);
    ypos = ypos - dist;
  }
  elem.style.left = xpos + "px";
  elem.style.top = ypos + "px";
  // 间隔一段适当的时间，再次调用同一个函数。
  var repeat = "moveElement('" + elementID + "'," + final_x + "," + final_y + "," + interval + ")";
  elem.movement = setTimeout(repeat, interval);
}

function convertToGS(img) {
  /*
    使用 <canvas> 对象在浏览器中把一幅彩色图片变成灰度图片，
    当用户的鼠标悬停到图片上面时，再把它切换回原始的彩色图片。
  */
  // 如果不支持 <canvas> 就返回
  if (!Modernizr.canvas) {
    return false;
  }
  // 存储原始的彩色版
  img.color = img.src;

  // 创建灰度版
  img.grayscale = createGSCanvas(img);

  // 在 onmouseover 或 onmouseout 事件发生时切换图片
  img.onmouseover = function() {
    this.src = this.color;
  };
  img.onmouseout = function() {
    this.src = this.grayscale;
  };

  img.onmouseout(); // ??
}

function createGSCanvas(img) {
  /*
    将给定的 img 编码成灰阶图像返回
  */
  var canvas = document.createElement("canvas");
  canvas.width = img.width;
  canvas.height = img.height;

  var ctx = canvas.getContext("2d");
  ctx.drawImage(img, 0, 0);

  var c = ctx.getImageData(0, 0, img.width, img.height);
  for (i = 0; i < c.height; i++) {
    for (j = 0; j < c.width; j++) {
      var x = (i * 4) * c.width + (j * 4);
      var r = c.data[x];
      var g = c.data[x + 1];
      var b = c.data[x + 2];
      c.data[x] = c.data[x + 1] = c.data[x + 2] = (r + g + b)/3;
    }
  }

  ctx.putImageData(c, 0, 0, 0, 0, c.width, c.height);

  return canvas.toDataURL();
}
