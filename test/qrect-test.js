const qt = require('../');
const expect = require('chai').expect;

describe('Test QRect class', () => {
    it('should create QRect with constructor', () => {
        const qrect1 = new qt.QRect();
        expect(qrect1 instanceof qt.QRect).to.equal(true);
        // TODO: (QPoint, QSize)
        const qrect2 = new qt.QRect(11, 13, 17, 19);
        expect(qrect2.x).to.equal(11);
        expect(qrect2.y).to.equal(13);
        expect(qrect2.width).to.equal(17);
        expect(qrect2.height).to.equal(19);
    });
    it('should create QRect with function', () => {
        const qrect1 = qt.QRect();
        expect(qrect1 instanceof qt.QRect).to.equal(true);
        // TODO: (QPoint, QPoint) - to write test
        // TODO: (Qpoint, QSize)
        const qrect2 = qt.QRect(11, 13, 17, 19);
        expect(qrect2.x).to.equal(11);
        expect(qrect2.y).to.equal(13);
        expect(qrect2.width).to.equal(17);
        expect(qrect2.height).to.equal(19);
    });
    it('should create QRect with (QPoint, QPoint)', () => {
        const qp1 = new qt.QPoint(5, 5);
        const qp2 = new qt.QPoint(50, 50);
        const qr1 = new qt.QRect(qp1, qp2);
        expect(qr1.x).to.equal(5);
        expect(qr1.y).to.equal(5);
        expect(qr1.width).to.equal(46);
        expect(qr1.height).to.equal(46);
    });
    it.only('should create QRect with (QPoint, QSize)', () => {
        const p = new qt.QPoint(5, 5);
        const s = new qt.QSize(50, 50);
        const qr1 = new qt.QRect(p, s);
        expect(qr1.x).to.equal(5);
        expect(qr1.y).to.equal(5);
        expect(qr1.width).to.equal(50);
        expect(qr1.height).to.equal(50);
    });
    it('should test x/y/width/height set/get', () => {
        const qrect1 = qt.QRect(11, 13, 17, 19);
        expect(qrect1.x).to.equal(11);
        expect(qrect1.y).to.equal(13);
        expect(qrect1.width).to.equal(17);
        expect(qrect1.height).to.equal(19);
        qrect1.x = 12;
        qrect1.y = 14;
        qrect1.width = 18;
        qrect1.height = 20;
        expect(qrect1.x).to.equal(12);
        expect(qrect1.y).to.equal(14);
        expect(qrect1.width).to.equal(18);
        expect(qrect1.height).to.equal(20);
    });
    it('should test adjust/adjusted', () => {
        const qrect1 = qt.QRect(11, 13, 17, 19);
        qrect1.adjust(1, 1, 1, 1);
        expect(qrect1.x).to.equal(12);
        expect(qrect1.y).to.equal(14);
        expect(qrect1.width).to.equal(17);
        expect(qrect1.height).to.equal(19);
        const qrect2 = qt.QRect(11, 13, 17, 19);
        const qrect3 = qrect2.adjusted(1, 1, 1, 1);
        expect(qrect3.x).to.equal(12);
        expect(qrect3.y).to.equal(14);
        expect(qrect3.width).to.equal(17);
        expect(qrect3.height).to.equal(19);
    });
    it('should test bottom()', () => {
        const qrect1 = qt.QRect(11, 13, 17, 19);
        expect(qrect1.bottom).to.equal(13 + 19 - 1);
    });
    it('should test bottomLeft()', () => {
        const qrect1 = qt.QRect(11, 13, 17, 19);
        const qpoint1 = qrect1.bottomLeft();
        expect(qpoint1.x).to.equal(11);
        expect(qpoint1.y).to.equal(13 + 19 - 1);
        expect(qpoint1 instanceof qt.QPoint).to.equal(true);
    });
    xit('should test bottomRight()', () => {
        const qrect1 = qt.QRect(11, 13, 17, 19);
        const qpoint1 = qrect1.bottomRight();
        expect(qpoint1.x).to.equal(11 + 17 - 1);
        expect(qpoint1.y).to.equal(13 + 19 - 1);
        expect(qpoint1 instanceof qt.QPoint).to.equal(true);
    });
    xit('should test center()', () => {
        const qrect1 = qt.QRect(11, 13, 17, 19);
        const qpoint1 = qrect1.center();
        expect(qpoint1.x).to.equal(19);
        expect(qpoint1.y).to.equal(22);
        expect(qpoint1 instanceof qt.QPoint).to.equal(true);
    });
    it('should test contains()', () => {
        const qrect1 = qt.QRect(11, 13, 17, 19);
        expect(qrect1.contains(5, 5)).to.equal(false);
        expect(qrect1.contains(15, 15)).to.equal(true);
    });
    it('should test intersect/intersected');
    it('should test isValid() isEmpty() isNull()', () => {
        const qrect1 = qt.QRect(11, 13, 17, 19);
        expect(qrect1.isEmpty()).to.equal(false);
        expect(qrect1.isValid()).to.equal(true);
        expect(qrect1.isNull()).to.equal(false);
        qrect1.left = 100;
        qrect1.top = 100;
        expect(qrect1.isEmpty()).to.equal(true);
        expect(qrect1.isValid()).to.equal(false);
        qrect1.width = 0;
        qrect1.height = 0;
        expect(qrect1.isNull()).to.equal(true);
    });
});
