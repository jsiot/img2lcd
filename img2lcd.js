"use strict";

var fs = require('fs');
var os = require('os');
var crypto = require('crypto');
var path = require('path');

var pngparse = require('pngparse');
var mime = require('mime');
var Jimp = require('jimp');

function Img2Lcd(){}

function getPixel(image, x, y) {
  x = x|0;
  y = y|0;

  if(x < 0 || y < 0 || x >= image.width || y >= image.height)
    return 0;

  var index = (y * image.width + x) * image.channels,
      r, g, b, a;

  switch(image.channels) {
    case 1:
      r = g = b = image.data[index];
      a = 255;
      break;

    case 2:
      r = g = b = image.data[index    ];
      a         = image.data[index + 1];
      break;

    case 3:
      r = image.data[index    ];
      g = image.data[index + 1];
      b = image.data[index + 2];
      a = 255;
      break;

    case 4:
      r = image.data[index    ];
      g = image.data[index + 1];
      b = image.data[index + 2];
      a = image.data[index + 3];
      break;
  }

  return ((r << 24) | (g << 16) | (b << 8) | a) >>> 0;
}


function hex2hex(hex) {
    for (var bytes = [], c = 0; c < hex.length; c += 2){
      bytes.push('0x'+hex.substr(c, 2));
    }
    return bytes;
}

function createImageData(image) {
  var buf = new Buffer(image.width * image.height * 4);

  var l = image.data.length;

  var pos = 0;
  for (var y = 0; y < image.height; y++) {
    for (var x = 0; x < image.width; x++) {
      buf.writeUInt32BE(getPixel(image, x, y), pos);
      pos += 4;
    }
  }

  image.data = buf;
  return image;
}

function tolcd(imgBuffer) {
  
    var pimage = createImageData(imgBuffer);

    var pixels = pimage.data; 
    var pixelsLen = pixels.length;
    var height = pimage.height;
    var width = pimage.width;
    var alpha = pimage.hasAlphaChannel;
    var threshold = 120;
    var unpackedBuffer = [];
    var depth = 4;

    // create a new buffer that will be filled with pixel bytes (8 bits per) and then returned
    var buffer = new Buffer((width * height) / 8);
    buffer.fill(0x00);
    
    var pixelVal;

    // filter pixels to create monochrome image data
    for (var i = 0; i < pixelsLen; i += depth) {
      // just take the red value
      pixelVal = pixels[i + 1] = pixels[i + 2] = pixels[i];

        // do threshold for determining on and off pixel vals
        if (pixelVal > threshold) {
          pixelVal = 1;
        } else {
          pixelVal = 0;
        }

      // push to unpacked buffer list
      unpackedBuffer[i/depth] = pixelVal;
    }

    // time to pack the buffer
    for (var i = 0; i < unpackedBuffer.length; i++) {
      // math
      var x = Math.floor(i % width);
      var y = Math.floor(i / width);

      // create a new byte, set up page position
      var byte = 0,
          page = Math.floor(y / 8),
          pageShift = 0x01 << (y - 8 * page);

      // is the first page? Just assign byte pos to x value, otherwise add rows to it too
      (page === 0) ? byte = x : byte = x + width * page; 
      
      if (unpackedBuffer[i] === 0) {
        // 'off' pixel
        buffer[byte] &= ~pageShift;
        
      } else {
        // 'on' pixel
        buffer[byte] |= pageShift;
      }
    }
     
    return buffer;
}

function pngtolcd(filename, cb) {
  pngparse.parseFile(filename, function(err, img) {
    if (err) {
      return cb(err);
    }     
    var buffer = tolcd(img);
    cb(err, buffer)
  });
}

Img2Lcd.prototype.convert = function(filename, cb) {
   var ext = mime.lookup(filename);

   switch(ext) {
       case 'image/png': 
         pngtolcd(filename, function(err, buffer) {
		   err ? cb(err, null) : cb(null, hex2hex(buffer.toString('hex')).join(','));
         });    
       break;
       
       case 'image/bmp':
         new Jimp(filename, function(err, image){
         	 var uname = "krambil";
         	 var hashname = crypto.createHash('md5').update(uname).digest('hex')+'.png';
         	 var tmppath = path.join(os.tmpdir(), hashname);
             
             image.write(tmppath);
         	 
         	 pngtolcd(tmppath, function(err, buffer) {
			     err ? cb(err, null) : cb(null, hex2hex(buffer.toString('hex')).join(','));
             });
         })

       break;

       default:
         console.log('not implemented yet');
       break;
   }
}

Img2Lcd.prototype.pngtohexarray = function(filename, callback) {
    pngtolcd(filename, function(err, buffer) {
		if(err) {
		  callback(err, null);
		} else {
	      callback(null, hex2hex(buffer.toString('hex')));
	    }
    });	
}

module.exports = new Img2Lcd();