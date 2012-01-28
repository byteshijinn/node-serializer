var path;
if (/win/i.test(process.platform)) {
	path = './Release/serializer.node';
} else {
	path = './out/Release/serializer.node';
}
module.exports = require(path);