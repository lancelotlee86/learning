var lennon = Object();
lennon.name = "John";
lennon.year = 1940;

var beatles = Object();
beatles.vocalist = lennon;

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

function prepareLinks() {
  if (!document.getElementsByTagName) return false;
  // test if getElementsByTagName is surported
  var links = document.getElementsByTagName('a');
  for (var i=0; i<links.length; i++) {
    if (links[i].getAttribute("class") == "popup") {
      links[i].onclick = function() {
        popUp(this.getAttribute("href"));
        return false;
      }
    }
  }
}

function innerHTMLTest() {
  var testdiv = document.getElementById("testdiv");
  testdiv.innerHTML = "<p>I inserted <em>this</em> content by innerHTML.</p>";
}

function popUp(winURL) {
  // 打开一个新窗口
  window.open(winURL, 'popup', 'width=320, height=480');
  // window.open(url, name, features)
}

function test(){
  // createElement
  var para = document.createElement("p");
  var testdiv = document.getElementById("testdiv2");
  // appendChild
  testdiv.appendChild(para)
  // createTextNode
  var txt = document.createTextNode("Hello World");
  para.appendChild(txt);
}

addLoadEvent(prepareLinks);
addLoadEvent(innerHTMLTest);
addLoadEvent(test);
