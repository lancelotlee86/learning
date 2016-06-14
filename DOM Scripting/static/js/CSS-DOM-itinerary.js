function stripeTables() {
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
        // rows[j].style.backgroundColor = "#ffc";  这样直接修改 style 属性不好，看下面的方法。
        addClass(rows[j], "odd"); // 自定义的函数，见 tools.js，追加或添加 class 属性值。
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

addLoadEvent(stripeTables);
addLoadEvent(displayAbbreviations);
addLoadEvent(highlightRows);
