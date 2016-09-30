const exec = require('child_process').exec;
const execSync = require('child_process').execSync;
const fs = require('fs');
const path = require('path');
const os = require('os');
var flag = process.argv[2] || "--exists";
const QT5_LIBS = ['Qt5Core', 'Qt5Gui', 'Qt5Test', 'Qt5Widgets'];
const QMAKE_QT5_VERSION = /Qt version 5/;
const ADDITIONAL_QT5_INCLUDE_FOLDERS = ['ActiveQt'];

function main() {
	exec('pkg-config ' + QT5_LIBS.join(' ') + ' ' + flag, function (err, stdout, stderr) {
		if (err) {
			if (process.platform === 'win32') {
				fallback();
			} else {
				throw new Error('ERROR: failed to run: pkg-config', opencv, flag);
			}
		} else {
			console.log(stdout);
		}
	});
}

// win32

function fallback() {
	exec('where qmake', function (err, stdout, stderr) {
		if (err) {
			throw new Error('Could not find qmake.');
		} else {
			stdout.split(os.EOL).filter(p => p.length > 0).filter(isQt5).map(path.dirname).map(printPaths);
		}
	});
}

function isQt5(qmake) {
	try {
		const result = execSync(qmake + ' -v').toString();
		if (QMAKE_QT5_VERSION.test(result)) {
			return true;
		}
	} catch(err) {
		return false;
	}
}

function printPaths(qmake_dirname) {
	if (flag === '--cflags') {
		const include_basepath = path.join(qmake_dirname, '../include')
		// outputs include dir
		console.log(include_basepath.replace(/\\/g, '\\\\'));
		fs.readdirSync(include_basepath).filter(item => {
			return item.slice(0, 2) === 'Qt' || ADDITIONAL_QT5_INCLUDE_FOLDERS.indexOf(item) !== -1;
		}).forEach(item => {
			// outputs per module dir
			console.log(path.join(include_basepath, item).replace(/\\/g, '\\\\'));
		});
	} else if (flag === '--libs') {
		const libPath = path.join(qmake_dirname, '../lib');
		const libs = fs.readdirSync(libPath).reduce((prev, file) => {
			if (path.extname(file) === '.lib') {
				prev += path.join(libPath, file) + os.EOL;
			}
			return prev;
		}, '');
		console.log(libs.replace(/\\/g, '\\\\'));
	} else {
		throw new Error('Unknown argument: ' + flag);
	}
}

main();