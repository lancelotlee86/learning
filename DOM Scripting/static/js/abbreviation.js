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
    var elem = quoteChildren[quoteChildren.length - 1]  // elem 包含着链接插入位置的节点
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

addLoadEvent(displayAbbreviations);
addLoadEvent(displayCitations);
addLoadEvent(displayAccesskeys);
