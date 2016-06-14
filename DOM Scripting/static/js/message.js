function positionMessage() {
  if (!document.getElementById) {
    return false;
  }
  if (!document.getElementById("message")) {
    return false;
  }
  // message 元素的移动
  var elem = document.getElementById("message");
  elem.style.position = "absolute";
  elem.style.left = "50px";
  elem.style.top = "100px";
  moveElement("message", 125, 25, 12);
  // message2 元素的移动
  var elem = document.getElementById("message2");
  elem.style.position = "absolute";
  elem.style.left = "50px";
  elem.style.top = "50px";
  moveElement("message2", 125, 125, 12);
}
/*
function moveMessage() {
  if (!document.getElementById) {
    return false;
  }
  if (!document.getElementById("message")) {
    return false;
  }
  var elem = document.getElementById("message");
  // 获取元素当前位置

  var xpos = parseInt(elem.style.left);
  var ypos = parseInt(elem.style.top);
  // 如果元素已经到达它的目的地，则退出这个函数
  if (xpos == 200 && ypos == 100) {
    return true;
  }
  if (xpos < 200) {
    xpos++;
  }
  if (xpos > 200) {
    xpos--;
  }
  if (ypos < 100) {
    ypos++;
  }
  if (ypos > 100) {
    ypos--;
  }
  elem.style.left = xpos + "px";
  elem.style.top = ypos + "px";
  movement = setTimeout("moveMessage()", 10);

  // elem.style.left = "200px";
}
*/
function moveElement(elementID, final_x, final_y, interval) {
  if (!document.getElementById) {
    return false;
  }
  if (!document.getElementById(elementID)) {
    return false;
  }
  // 取得要移动的元素的对象
  var elem = document.getElementById(elementID);
  // 获取元素当前位置
  var xpos = parseInt(elem.style.left);
  var ypos = parseInt(elem.style.top);
  // 如果元素已经到达它的目的地，则退出这个函数
  if (xpos == final_x && ypos == final_y) {
    return true;
  }
  // 如果元素还没有到目的地，则将其坐标设置的更靠近一个像素
  if (xpos < final_x) {
    xpos++;
  }
  if (xpos > final_x) {
    xpos--;
  }
  if (ypos < final_y) {
    ypos++;
  }
  if (ypos > final_y) {
    ypos--;
  }
  elem.style.left = xpos + "px";
  elem.style.top = ypos + "px";
  // 间隔一段适当的时间，再次调用同一个函数。
  var repeat = "moveElement('" + elementID + "'," + final_x + "," + final_y + "," + interval + ")";
  movement = setTimeout(repeat, interval);
}

addLoadEvent(positionMessage);
// addLoadEvent(moveMessage); 在调用 positionMessage 函数中调用 moveMessage 了
