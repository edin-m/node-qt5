const qt = require('../hello');
const expect = require('chai').expect;

const DELTA = 0.000999;

describe('Test QPointF', () => {
	const obj1 = { x: 1.134, y: 2.258 };
	const obj2 = { x: 5.782, y: 2.584 };
	const point = new qt.QPointF(obj1.x, obj1.y);
	it('should do sanity test', () => {
		expect(2 + 2).to.equal(4);
	});
	it('should create without new');
	it('should create with new and set get x y', () => {
		expect(point.x()).to.be.within(obj1.x, obj1.x + DELTA);
		expect(point.y()).to.be.within(obj1.y, obj1.y + DELTA);
		point.setX(obj2.x);
		expect(point.x()).to.be.within(obj2.x, obj2.x + DELTA);
		point.setY(obj2.y);
		expect(point.y()).to.be.within(obj2.y, obj2.y + DELTA);
	});
	it('should test multiply()');
	it('should test plus()');
	it('should test minus()');
	it('should test divide()');
});