const qt = require('../../');

function main() {
    const app = new qt.QApplication();
    const w = new qt.QWidget();
    const b = new qt.QPushButton('wicked', w);
    setTimeout(() => {
        w.resize(600, 600);
    }, 4000);

    w.show();

    const res = app.exec();
    console.log('exec res', res);
}

main();
