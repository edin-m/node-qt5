const qt = require('../hello');
const expect = require('chai').expect;

describe.skip('Test QPoint', () => {
	it('should do sanity test', () => {
		expect(2 + 2).to.equal(4);
	});
	it('should create without new');
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