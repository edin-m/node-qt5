const qt = require('../');
const expect = require('chai').expect;

describe('Test QRect class', () => {
  it('should create QRect with constructor', () => {
  	const qrect1 = new qt.QRect();
  	expect(qrect1 instanceof qt.QRect).to.equal(true);
  	// TODO: (QPoint, QPoint)
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
  	// TODO: (QPoint, QPoint)
  	// TODO: (Qpoint, QSize)
  	const qrect2 = qt.QRect(11, 13, 17, 19);
  	expect(qrect2.x).to.equal(11);
  	expect(qrect2.y).to.equal(13);
  	expect(qrect2.width).to.equal(17);
  	expect(qrect2.height).to.equal(19);
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
});