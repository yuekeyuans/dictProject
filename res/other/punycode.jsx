'use strict';

function _toConsumableArray(arr) { return _arrayWithoutHoles(arr) || _iterableToArray(arr) || _nonIterableSpread(); }

function _nonIterableSpread() { throw new TypeError("Invalid attempt to spread non-iterable instance"); }

function _iterableToArray(iter) { if (Symbol.iterator in Object(iter) || Object.prototype.toString.call(iter) === "[object Arguments]") return Array.from(iter); }

function _arrayWithoutHoles(arr) { if (Array.isArray(arr)) { for (var i = 0, arr2 = new Array(arr.length); i < arr.length; i++) { arr2[i] = arr[i]; } return arr2; } }

var maxInt = 2147483647; // aka. 0x7FFFFFFF or 2^31-1

/** Bootstring parameters */

var base = 36;
var tMin = 1;
var tMax = 26;
var skew = 38;
var damp = 700;
var initialBias = 72;
var initialN = 128; // 0x80

var delimiter = '-'; // '\x2D'

/** Regular expressions */

var regexPunycode = /^xn--/;
var regexNonASCII = /[^\0-\x7E]/; // non-ASCII chars

var regexSeparators = /[\x2E\u3002\uFF0E\uFF61]/g; // RFC 3490 separators

/** Error messages */

var errors = {
  'overflow': 'Overflow: input needs wider integers to process',
  'not-basic': 'Illegal input >= 0x80 (not a basic code point)',
  'invalid-input': 'Invalid input'
};
/** Convenience shortcuts */

var baseMinusTMin = base - tMin;
var floor = Math.floor;
var stringFromCharCode = String.fromCharCode;

function error(type) {
  throw new RangeError(errors[type]);
}

function map(array, fn) {
  var result = [];
  var length = array.length;

  while (length--) {
    result[length] = fn(array[length]);
  }

  return result;
}

function mapDomain(string, fn) {
  var parts = string.split('@');
  var result = '';

  if (parts.length > 1) {
    // In email addresses, only the domain name should be punycoded. Leave
    // the local part (i.e. everything up to `@`) intact.
    result = parts[0] + '@';
    string = parts[1];
  } // Avoid `split(regex)` for IE8 compatibility. See #17.


  string = string.replace(regexSeparators, '\x2E');
  var labels = string.split('.');
  var encoded = map(labels, fn).join('.');
  return result + encoded;
}

function ucs2decode(string) {
  var output = [];
  var counter = 0;
  var length = string.length;

  while (counter < length) {
    var value = string.charCodeAt(counter++);

    if (value >= 0xD800 && value <= 0xDBFF && counter < length) {
      // It's a high surrogate, and there is a next character.
      var extra = string.charCodeAt(counter++);

      if ((extra & 0xFC00) == 0xDC00) {
        // Low surrogate.
        output.push(((value & 0x3FF) << 10) + (extra & 0x3FF) + 0x10000);
      } else {
        // It's an unmatched surrogate; only append this code unit, in case the
        // next code unit is the high surrogate of a surrogate pair.
        output.push(value);
        counter--;
      }
    } else {
      output.push(value);
    }
  }

  return output;
}

function ucs2encode(array) {
  return String.fromCodePoint.apply(String, _toConsumableArray(array));
};

function basicToDigit(codePoint) {
  if (codePoint - 0x30 < 0x0A) {
    return codePoint - 0x16;
  }

  if (codePoint - 0x41 < 0x1A) {
    return codePoint - 0x41;
  }

  if (codePoint - 0x61 < 0x1A) {
    return codePoint - 0x61;
  }

  return base;
};

function digitToBasic(digit, flag) {
  //  0..25 map to ASCII a..z or A..Z
  // 26..35 map to ASCII 0..9
  return digit + 22 + 75 * (digit < 26) - ((flag != 0) << 5);
};

function adapt(delta, numPoints, firstTime) {
  var k = 0;
  delta = firstTime ? floor(delta / damp) : delta >> 1;
  delta += floor(delta / numPoints);

  for (;
  /* no initialization */
  delta > baseMinusTMin * tMax >> 1; k += base) {
    delta = floor(delta / baseMinusTMin);
  }

  return floor(k + (baseMinusTMin + 1) * delta / (delta + skew));
};

function decode(input) {
  // Don't use UCS-2.
  var output = [];
  var inputLength = input.length;
  var i = 0;
  var n = initialN;
  var bias = initialBias; // Handle the basic code points: let `basic` be the number of input code
  // points before the last delimiter, or `0` if there is none, then copy
  // the first basic code points to the output.

  var basic = input.lastIndexOf(delimiter);

  if (basic < 0) {
    basic = 0;
  }

  for (var j = 0; j < basic; ++j) {
    // if it's not a basic code point
    if (input.charCodeAt(j) >= 0x80) {
      error('not-basic');
    }

    output.push(input.charCodeAt(j));
  } // Main decoding loop: start just after the last delimiter if any basic code
  // points were copied; start at the beginning otherwise.


  for (var index = basic > 0 ? basic + 1 : 0; index < inputLength;)
  /* no final expression */
  {
    // `index` is the index of the next character to be consumed.
    // Decode a generalized variable-length integer into `delta`,
    // which gets added to `i`. The overflow checking is easier
    // if we increase `i` as we go, then subtract off its starting
    // value at the end to obtain `delta`.
    var oldi = i;

    for (var w = 1, k = base;;
    /* no condition */
    k += base) {
      if (index >= inputLength) {
        error('invalid-input');
      }

      var digit = basicToDigit(input.charCodeAt(index++));

      if (digit >= base || digit > floor((maxInt - i) / w)) {
        error('overflow');
      }

      i += digit * w;
      var t = k <= bias ? tMin : k >= bias + tMax ? tMax : k - bias;

      if (digit < t) {
        break;
      }

      var baseMinusT = base - t;

      if (w > floor(maxInt / baseMinusT)) {
        error('overflow');
      }

      w *= baseMinusT;
    }

    var out = output.length + 1;
    bias = adapt(i - oldi, out, oldi == 0); // `i` was supposed to wrap around from `out` to `0`,
    // incrementing `n` each time, so we'll fix that now:

    if (floor(i / out) > maxInt - n) {
      error('overflow');
    }

    n += floor(i / out);
    i %= out; // Insert `n` at position `i` of the output.

    output.splice(i++, 0, n);
  }

  return String.fromCodePoint.apply(String, output);
};

// function encode(input) {
//   var output = []; // Convert the input in UCS-2 to an array of Unicode code points.

//   input = ucs2decode(input); // Cache the length.

//   var inputLength = input.length; // Initialize the state.

//   var n = initialN;
//   var delta = 0;
//   var bias = initialBias; // Handle the basic code points.

//   var _iteratorNormalCompletion = true;
//   var _didIteratorError = false;
//   var _iteratorError = undefined;

//   try {
//     for (var _iterator = input[Symbol.iterator](), _step; !(_iteratorNormalCompletion = (_step = _iterator.next()).done); _iteratorNormalCompletion = true) {
//       var _currentValue2 = _step.value;

//       if (_currentValue2 < 0x80) {
//         output.push(stringFromCharCode(_currentValue2));
//       }
//     }
//   } catch (err) {
//     _didIteratorError = true;
//     _iteratorError = err;
//   } finally {
//     try {
//       if (!_iteratorNormalCompletion && _iterator.return != null) {
//         _iterator.return();
//       }
//     } finally {
//       if (_didIteratorError) {
//         throw _iteratorError;
//       }
//     }
//   }

//   var basicLength = output.length;
//   var handledCPCount = basicLength; // `handledCPCount` is the number of code points that have been handled;
//   // `basicLength` is the number of basic code points.
//   // Finish the basic string with a delimiter unless it's empty.

//   if (basicLength) {
//     output.push(delimiter);
//   } // Main encoding loop:


//   while (handledCPCount < inputLength) {
//     // All non-basic code points < n have been handled already. Find the next
//     // larger one:
//     var m = maxInt;
//     var _iteratorNormalCompletion2 = true;
//     var _didIteratorError2 = false;
//     var _iteratorError2 = undefined;

//     try {
//       for (var _iterator2 = input[Symbol.iterator](), _step2; !(_iteratorNormalCompletion2 = (_step2 = _iterator2.next()).done); _iteratorNormalCompletion2 = true) {
//         var currentValue = _step2.value;

//         if (currentValue >= n && currentValue < m) {
//           m = currentValue;
//         }
//       } // Increase `delta` enough to advance the decoder's <n,i> state to <m,0>,
//       // but guard against overflow.

//     } catch (err) {
//       _didIteratorError2 = true;
//       _iteratorError2 = err;
//     } finally {
//       try {
//         if (!_iteratorNormalCompletion2 && _iterator2.return != null) {
//           _iterator2.return();
//         }
//       } finally {
//         if (_didIteratorError2) {
//           throw _iteratorError2;
//         }
//       }
//     }

//     var handledCPCountPlusOne = handledCPCount + 1;

//     if (m - n > floor((maxInt - delta) / handledCPCountPlusOne)) {
//       error('overflow');
//     }

//     delta += (m - n) * handledCPCountPlusOne;
//     n = m;
//     var _iteratorNormalCompletion3 = true;
//     var _didIteratorError3 = false;
//     var _iteratorError3 = undefined;

//     try {
//       for (var _iterator3 = input[Symbol.iterator](), _step3; !(_iteratorNormalCompletion3 = (_step3 = _iterator3.next()).done); _iteratorNormalCompletion3 = true) {
//         var _currentValue = _step3.value;

//         if (_currentValue < n && ++delta > maxInt) {
//           error('overflow');
//         }

//         if (_currentValue == n) {
//           // Represent delta as a generalized variable-length integer.
//           var q = delta;

//           for (var k = base;;
//           /* no condition */
//           k += base) {
//             var t = k <= bias ? tMin : k >= bias + tMax ? tMax : k - bias;

//             if (q < t) {
//               break;
//             }

//             var qMinusT = q - t;
//             var baseMinusT = base - t;
//             output.push(stringFromCharCode(digitToBasic(t + qMinusT % baseMinusT, 0)));
//             q = floor(qMinusT / baseMinusT);
//           }

//           output.push(stringFromCharCode(digitToBasic(q, 0)));
//           bias = adapt(delta, handledCPCountPlusOne, handledCPCount == basicLength);
//           delta = 0;
//           ++handledCPCount;
//         }
//       }
//     } catch (err) {
//       _didIteratorError3 = true;
//       _iteratorError3 = err;
//     } finally {
//       try {
//         if (!_iteratorNormalCompletion3 && _iterator3.return != null) {
//           _iterator3.return();
//         }
//       } finally {
//         if (_didIteratorError3) {
//           throw _iteratorError3;
//         }
//       }
//     }

//     ++delta;
//     ++n;
//   }
//   return output.join('');
// };

function toUnicode(input) {
  return mapDomain(input, function (string) {
    return regexPunycode.test(string) ? decode(string.slice(4).toLowerCase()) : string;
  });
};

function toASCII(input) {
  return mapDomain(input, function (string) {
    return regexNonASCII.test(string) ? 'xn--' + encode(string) : string;
  });
};


if (!String.fromCodePoint) (function(stringFromCharCode) {
    var fromCodePoint = function(_) {
      var codeUnits = [], codeLen = 0, result = "";
      for (var index=0, len = arguments.length; index !== len; ++index) {
        var codePoint = +arguments[index];
        // correctly handles all cases including `NaN`, `-Infinity`, `+Infinity`
        // The surrounding `!(...)` is required to correctly handle `NaN` cases
        // The (codePoint>>>0) === codePoint clause handles decimals and negatives
        if (!(codePoint < 0x10FFFF && (codePoint>>>0) === codePoint))
          throw RangeError("Invalid code point: " + codePoint);
        if (codePoint <= 0xFFFF) { // BMP code point
          codeLen = codeUnits.push(codePoint);
        } else { // Astral code point; split in surrogate halves
          // https://mathiasbynens.be/notes/javascript-encoding#surrogate-formulae
          codePoint -= 0x10000;
          codeLen = codeUnits.push(
            (codePoint >> 10) + 0xD800,  // highSurrogate
            (codePoint % 0x400) + 0xDC00 // lowSurrogate
          );
        }
        if (codeLen >= 0x3fff) {
          result += stringFromCharCode.apply(null, codeUnits);
          codeUnits.length = 0;
        }
      }
      return result + stringFromCharCode.apply(null, codeUnits);
    };
    try { // IE 8 only supports `Object.defineProperty` on DOM elements
      Object.defineProperty(String, "fromCodePoint", {
        "value": fromCodePoint, "configurable": true, "writable": true
      });
    } catch(e) {
      String.fromCodePoint = fromCodePoint;
    }
}(String.fromCharCode));
