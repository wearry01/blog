const num_imgs = 30;
var order = [...Array(num_imgs).keys()];
var cur = num_imgs;

function randint(n) {
  return Math.floor(Math.random() * n);
}

function shuffleArray(array) {
  for (let i = array.length - 1; i > 0; i--) {
    const j = randint(i + 1);
    [array[i], array[j]] = [array[j], array[i]];
  }
}

function padding(n) {
  n = n + "";
  while (n.length < 5) {
    n = "0" + n;
  }
  return n;
}

function resampleGallery() {
  if (cur >= num_imgs) {
    shuffleArray(order);
    cur = 0;
  }
  var idx = 1 + order[cur];
  var img = document.getElementById("gallery-image");
  img.src = "images/gallery/img_" + padding(idx) + ".jpg";
  img.alt = "Gallery image " + padding(idx);
  cur += 1;
}

var span = document.getElementById("lucky");
var link = document.createElement("a");
var text = document.createTextNode("Random");
link.onclick = function() {
  resampleGallery();
  return false;
};
link.href = "javascript:;";
link.appendChild(text);
span.appendChild(link);
