var addon = require('bindings')('hello');

console.log(addon.hello()); // 'world'

module.exports = addon;
// module.exports.hello = addon.hello;

var Qt = {};

Qt.AspectRatioMode = {
	IgnoreAspectRatio: 0,
	KeepAspectRatio: 1,
	KeepAspectRatioByExpanding: 2
};

module.exports.Qt = Qt;