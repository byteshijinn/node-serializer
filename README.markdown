# node-serializer
node-serializer provide you a way to share session information with php. 

## Install Guide
### To build:
Unix:

    $node_source/tools/tools/gyp_addon serializer.gyp
    make

Windows:
first copy **node.lib** to this directory.

    $node_source/tools/tools/gyp_addon serializer.gyp
    "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"
    msbuild serializer.sln


## Tutorial
### Simple Sample

    var serializer = require('serializer');
    console.log(serializer
                .php_sess_unserialize('I|s:3:"Ray";Love|a:3:{s:4:"node";s:10:' 
                + '"nodejs.org";s:3:"npm";s:9:"npmjs.org";s:9:"socket.io";' 
                + 's:9:"socket.io";}NodeJS|d:INF;'));

Sample Output:

    { I: 'Ray',
      Love:
       { node: 'nodejs.org',
         npm: 'npmjs.org',
         'socket.io': 'socket.io' },
      NodeJS: Infinity }

## License
(The MIT License)

Copyright (c) 2011-2012 Zhao Lei and contributors

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.