const qt = require('../../');

function main() {
    const app = new qt.QApplication();
    const w = new qt.QWidget();

    w.show();
    w.resize(1000, 1000);

    // w.on(qt.QWidget.events.windowTitleChanged, function () {
    //     console.log('widget window title', w.windowTitle);
    // });

    setTimeout(() => {
        console.log('resize');
        w.resize(500, 500);
    }, 5000);

    const res = app.exec();
    console.log('exec res', res);

}

main();
