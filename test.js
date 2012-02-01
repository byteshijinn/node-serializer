var assert = require('assert')
    , util = require('util');
if (/win/i.test(process.platform)) {
    var serializer = require('./Debug/serializer');
} else {
    var serializer = require('./out/Debug/serializer');
}
var session_text = 'I|s:3:"Ray";Love|a:3:{s:4:"node";s:10:"nodejs.org";s:3:"npm";s:9:"npmjs.org";s:9:"socket.io";s:9:"socket.io";}NodeJS|d:INF;';
try {
    console.time("unserialize");
    var out = serializer.php_sess_unserialize(session_text);
    console.timeEnd("unserialize");
    assert.equal(serializer.php_sess_serialize(out), session_text, 'Not Equals.');
    console.log(out);
} catch (e) {
    console.log(e.toString());
}