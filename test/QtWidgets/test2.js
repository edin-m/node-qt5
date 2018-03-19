const EventEmitter = require('events');
const qt = require('../../');
const http = require('http');

function main() {
    const app = new qt.QApplication();

    const widget = new qt.QWidget();
    const label = new qt.QLabel('label');
    const button = new qt.QPushButton('Create server');

    button.on('clicked', (checked) => {
        console.log('CLICKED ======> ', checked);
    });

    console.log('asdfsfdsa', button instanceof EventEmitter);
    const layout = new qt.QHBoxLayout();
    layout.addWidget(label);
    layout.addWidget(button);
    widget.setLayout(layout);

    widget.show();

    const res = app.exec();

    console.log('WWWWWIIIICKKKKEEEDDDD');
}

main();
