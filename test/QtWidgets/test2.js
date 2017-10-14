const EventEmitter = require('events');
const qt = require('../../');
const http = require('http');

function main() {
    const app = new qt.QApplication();


    const widget = new qt.QWidget();
    const label = new qt.QLabel('label');
    const button = new qt.QPushButton('Create server');
    // button.wickedSick = 'wicked sick';

    console.log('asdfsfdsa', button instanceof EventEmitter);
    // button.on('clicked', (checked) => {
    //     console.log('clicked', checked);
    //     label.text = 'wicked';
    // });

    // setTimeout(() => {
    // button.setupConns();
    // }, 2000);

    // setTimeout(() => {
    //     console.log('emitting click');
    // //     button.emit('clicked');
    //     setTimeout(() => {
    //         console.log('emitting click');
    //         //     button.emit('clicked');
    //     }, 10000);
    // }, 2000);

    let data = 1;
    const dataInterval = setInterval(() => {
        console.log('===================> health check');
        label.text = `${data}`;
        data ++;
        if (data > 10) {
            clearInterval(dataInterval);
        }
    }, 1000);

    // button.on('clicked', () => {
    //     console.log('clicked');
    // });

    const layout = new qt.QHBoxLayout();
    layout.addWidget(label);
    layout.addWidget(button);
    widget.setLayout(layout);

    console.log('1');
    widget.show();
    console.log('2');

    const res = app.exec();
    console.log('exec res', res);
}

main();
