// getElementsByClassName()
// typeof
alert(typeof document.getElementById('purchases'));
alert(document.getElementsByClassName('important').length);

// getAttribute
var paras = document.getElementsByTagName('p');
for(var i=0; i<paras.length; i++) {
  var title_text = paras[i].getAttribute('title');
  if(title_text) {
    alert(title_text);
  }
}

// setAttribute
// 不会修改源文件
var shopping = document.getElementById('purchases');
alert(shopping.getAttribute('title'));
shopping.setAttribute('title', 'a list of goods');
alert(shopping.getAttribute('title'));
