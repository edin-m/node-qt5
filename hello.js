var addon = require('bindings')('hello');

console.log(addon.hello()); // 'world'

module.exports = addon;
// module.exports.hello = addon.hello;