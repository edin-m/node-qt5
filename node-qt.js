let qt;

// for IDE-syntax purposes
qt = {
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
        events: {
            windowTitleChanged: null
        }
    },
    QApplication: {
        exec: null
    },
    QPushButton: {
        
    }
};

qt = require('bindings')('node-qt');

qt.AspectRatio = {
    IgnoreAspectRatio: 0,
    KeepAspectRatio: 1,
    KeepAspectRatioByExpanding: 2
};

module.exports = qt;
