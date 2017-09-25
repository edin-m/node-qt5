const qt = require('../');
const expect = require('chai').expect;

describe('Test QPoint', () => {
    it('should create QPoint with constructor', () => {
        const qpoint1 = new qt.QPoint();
        expect(qpoint1 instanceof qt.QPoint).to.equal(true);
        const qpoint2 = new qt.QPoint(11, 13);
        expect(qpoint2.x).to.equal(11);
        expect(qpoint2.y).to.equal(13);
        const qpoint3 = new qt.QPoint(qpoint2);
        expect(qpoint3.x).to.equal(11);
        expect(qpoint3.y).to.equal(13);
    });
    it('should create QPoint without constructor', () => {
        const qpoint1 = qt.QPoint();
        expect(qpoint1 instanceof qt.QPoint).to.equal(true);
        const qpoint2 = qt.QPoint(11, 13);
        expect(qpoint2.x).to.equal(11);
        expect(qpoint2.y).to.equal(13);
        const qpoint3 = qt.QPoint(qpoint2);
        expect(qpoint3.x).to.equal(11);
        expect(qpoint3.y).to.equal(13);
    });
    it('should test x/y set/get', () => {
        const qpoint1 = new qt.QPoint(11, 13);
        expect(qpoint1.x).to.equal(11);
        expect(qpoint1.y).to.equal(13);
        qpoint1.x = 17;
        qpoint1.y = 19;
        expect(qpoint1.x).to.equal(17);
        expect(qpoint1.y).to.equal(19);
    });
    it('should test isNull()', () => {
        const qpoint1 = qt.QPoint();
        expect(qpoint1.isNull()).to.equal(true);
        qpoint1.x = 17;
        qpoint1.y = 19;
        expect(qpoint1.isNull()).to.equal(false);
    });
    it('should test manhattanLength()', () => {
        const qpoint1 = qt.QPoint(11, -13);
        expect(qpoint1.manhattanLength()).to.equal(Math.abs(11) + Math.abs(-13));
    });
    it('should test multiply operator', () => {
        const qpoint1 = qt.QPoint(11, 13);
        qpoint1.multiply(2);
        expect(qpoint1.x).to.equal(22);
        expect(qpoint1.y).to.equal(26);
        const qpoint2 = qt.QPoint(-1, 4);
        const qpoint3 = qpoint2.multiply(2.6);
        expect(qpoint3.x).to.equal(-3);
        expect(qpoint3.y).to.equal(10);
        expect(qpoint3 === qpoint2).to.equal(true);
    });
    it('should test plus operator', () => {
        const p = qt.QPoint(3, 7);
        const q = qt.QPoint(-1, 4);
        const qpoint = p.plus(q);
        expect(qpoint.x).to.equal(2);
        expect(qpoint.y).to.equal(11);
        expect(p.x).to.equal(2);
        expect(p.y).to.equal(11);
        expect(p === qpoint).to.equal(true);
    });
    it('should test minus operator', () => {
        const p = qt.QPoint(3, 7);
        const q = qt.QPoint(-1, 4);
        const qpoint = p.minus(q);
        expect(qpoint.x).to.equal(4);
        expect(qpoint.y).to.equal(3);
        expect(p.x).to.equal(4);
        expect(p.y).to.equal(3);
        expect(qpoint === p).to.equal(true);
    });
    it('should test divide operator', () => {
        const p = qt.QPoint(-3, 10);
        const qpoint = p.divide(2.5);
        expect(qpoint.x).to.equal(-1);
        expect(qpoint.y).to.equal(4);
        expect(p.x).to.equal(-1);
        expect(p.y).to.equal(4);
        expect(qpoint === p).to.equal(true);
    });
});
