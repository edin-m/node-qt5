const qt = require('../');
const expect = require('chai').expect;

describe('test QSize', () => {
    it('test QSize - new ctor', () => {
        const size1 = new qt.QSize();
        expect(size1 instanceof qt.QSize).to.equal(true);
        const size2 = new qt.QSize(11, 13);
        expect(size2.width).to.equal(11);
        expect(size2.height).to.equal(13);
    });
    it('test QSize - new ctor', () => {
        const size1 = qt.QSize();
        expect(size1 instanceof qt.QSize).to.equal(true);
        const size2 = qt.QSize(11, 13);
        expect(size2.width).to.equal(11);
        expect(size2.height).to.equal(13);
    });
    it('test width/height set/get', () => {
        const qrect1 = qt.QSize(11, 13);
        expect(qrect1.width).to.equal(11);
        expect(qrect1.height).to.equal(13);
        qrect1.width = 18;
        qrect1.height = 20;
        expect(qrect1.width).to.equal(18);
        expect(qrect1.height).to.equal(20);
    });
    it('test isNull', () => {
        const size = new qt.QSize(0, 0);
        expect(size.isNull()).to.equal(true);
        size.width = 1;
        expect(size.isNull()).to.equal(false);
    });
    it('test isValid', () => {
        const size = new qt.QSize(-1, -1);
        expect(size.isValid()).to.equal(false);
        size.width = 1;
        expect(size.isValid()).to.equal(false);
        size.height = 1;
        expect(size.isValid()).to.equal(true);
    });
    xit('asdfa', () => {
        const btn = new qt.QPushButton();
        btn.on('clicked', () => {
            console.log('wicked sick');
        });
    });
});
