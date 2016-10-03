const qt = require('../hello');
const expect = require('chai').expect;

describe('Test QPoint', () => {
	it('should do sanity test', () => {
		expect(2 + 2).to.equal(4);
	});
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
		const qpoint1 = qt.QPoint(11, 13);
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
	});
	it('should test plus operator', () => {
		const p = qt.QPoint(3, 7);
		const q = qt.QPoint(-1, 4);
		const qpoint = p.plus(q);
		expect(qpoint.x).to.equal(2);
		expect(qpoint.y).to.equal(11);
	});
	it('should test minus operator', () => {
		const p = qt.QPoint(3, 7);
		const q = qt.QPoint(-1, 4);
		const qpoint = p.minus(q);
		expect(qpoint.x).to.equal(4);
		expect(qpoint.y).to.equal(3);
	});
	it('should test divide operator', () => {
		const p = qt.QPoint(-3, 10);
		const qpoint = p.divide(2.6);
		expect(qpoint.x).to.equal(-1);
		expect(qpoint.y).to.equal(4);
	});
	describe.skip('', () => {
		it('should create with new and set get x y', () => {
			const point = new qt.QPoint(1, 2);
			expect(point.x()).to.equal(1);
			expect(point.y()).to.equal(2);
			point.setX(5);
			expect(point.x()).to.equal(5);
			point.setY(6);
			expect(point.y()).to.equal(6);
		});
		it('should test float numbers set get', () => {
			const point = new qt.QPoint(1.55, 2.66);
			expect(point.x()).to.equal(1);
			expect(point.y()).to.equal(2);
			point.setX(5.99);
			expect(point.x()).to.equal(5);
			point.setY(6.28);
			expect(point.y()).to.equal(6);
		});
		it('should test multiply()', () => {
			const point = new qt.QPoint(5, 10);
			point.multiply(2);
			expect(point.x()).to.equal(10);
			expect(point.y()).to.equal(20);
		});
		it('should test plus()', () => {
			const p1 = new qt.QPoint(2, 3);
			const p2 = new qt.QPoint(3, 4);
			p1.plus(p2);
			expect(p1.x()).to.equal(5);
			expect(p1.y()).to.equal(7);
		});
		it('should test minus()', () => {
			const p1 = new qt.QPoint(10, 11);
			const p2 = new qt.QPoint(4, 6);
			p1.minus(p2);
			expect(p1.x()).to.equal(6);
			expect(p1.y()).to.equal(5);
		});
		it('should test divide()', () => {
			const p1 = new qt.QPoint(10, 20);
			p1.divide(2);
			expect(p1.x()).to.equal(5);
			expect(p1.y()).to.equal(10);
		});
	});
});