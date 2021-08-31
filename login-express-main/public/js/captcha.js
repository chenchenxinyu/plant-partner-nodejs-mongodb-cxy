function createCode() {
    let code = "";
    var codeLength = 4;
    var selectChar = new Array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z');
    for (var i = 0; i < codeLength; i++) {
        var charIndex = Math.floor(Math.random() * 36);
        code += selectChar[charIndex];
    }
    return code;
}

function draw_canvas(code) {
    if (canvas) {
        var ctx=canvas.getContext('2d');
        ctx.clearRect(0,0,canvas.width,canvas.height);
        ctx.font="80px Verdana";
        ctx.strokeText(code,50,150);
        console.log("canvas 绘制完成")
    }
    else
        console.log("没有找到canvas")
}

function isequal(str,str1,alert_info){
    if(str != str1){
      alert(alert_info);
      return false;}
    else return true;
  }

exports.createCode = createCode;
exports.draw_canvas = draw_canvas;
exports.isequal = isequal;