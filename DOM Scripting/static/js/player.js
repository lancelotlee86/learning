function createVideoControls() {
  // 找到页面中的 video 元素，然后分别对它们应用 addControls 函数
  var vids = document.getElementsByTagName("video");
  for (var i = 0; i < vids.length; i++) {
    addControls(vids[i]);
  }
}

function addControls(vid) {

  // 删除 video 元素原来的 controls 属性，从而去掉其内置的控件
  vid.removeAttribute("controls");

  vid.height = vid.videoHeight;
  vid.width = vid.videoWidth;
  vid.parentNode.style.height = vid.videoHeight + 'px';
  vid.parentNode.style.width = vid.videoWidth + 'px';

  var controls = document.createElement("div");
  controls.setAttribute("class", "controls");

  var play = document.createElement("button");
  play.setAttribute("title", "Play");
  play.innerHTML = '&#x25BA;';  // 这是一个 utf-8 编码的符号

  controls.appendChild(play);

  vid.parentNode.insertBefore(controls, vid);

  // 给 Play 按钮添加一个 click 事件，以便单击它播放影片
  play.onclick = function() {
    if (vid.ended) {
      vid.currentTime = 0;
    }
    if (vid.paused) {
      vid.play();
    } else {
      vid.pause();
    }
  };

  // 利用 play, pause 和 ended 事件来修改 Play 按钮的状态
  // addEventListener 方法是为对象添加事件处理函数的规范方法。
  vid.addEventListener("play", function() {
    play.innerHTML = '&#2590;&#2590;';
    play.setAttribute("paused", true);
  }, false);

  vid.addEventListener("pause", function() {
    play.removeAttribute("paused");
    play.innerHTML = '&#x25BA;';
  }, false);

  vid.addEventListener("ended", function() {
    vid.pause();
  }, false);
}

addLoadEvent(createVideoControls);
