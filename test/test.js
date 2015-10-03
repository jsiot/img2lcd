var img2lcd = require('../img2lcd.js');

img2lcd.convert('./test/images/robot.png', function(err, hex){
    if(!err) {
      console.log(hex);
    }
})