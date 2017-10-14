// for IDE auto-complete purposes
let qt = {
    QPoint: {
        isNull: null,
        multiply: null,
        plus: null,
        minus: null,
        divide: null
    },
    QSize: {
        isValid: null,
        isNull: null
    },
    QRect: null,
    QWidget: {
        show: null,
        resize: null,
        windowTitle: null,
        setLayout: null,
        events: {
            windowTitleChanged: null
        }
    },
    QApplication: {
        exec: null
    },
    QPushButton: {
        on: null,
        signals: {
            clicked: null
        }
    },
    QLabel: {
        text: null
    },
    QHBoxLayout: {
        addWidget: () => {},
        setLayout: () => {},
    }
};

qt = require('bindings')('node-qt');

qt.AspectRatio = {
    IgnoreAspectRatio: 0,
    KeepAspectRatio: 1,
    KeepAspectRatioByExpanding: 2
};

const EventEmitter = require('events');
const util = require('util');

util.inherits(qt.QPushButton, EventEmitter);

// qt.QPushButton.prototype.emitx = function(...args) {
//     console.log('EMIT XXX');
//     console.log(this, this instanceof qt.QPushButton, ...args);
//     this.emit('clicked');
// };

module.exports = qt;
