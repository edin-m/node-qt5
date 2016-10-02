const qt = require('../');
const expect = require('chai').expect;

describe('Test QSize class', () => {
  it('should do sanity test', () => {
  	expect(2 + 2).to.equal(4);
  })
  it('should create QSize with constructor', () => {
  	const qsize1 = new qt.QSize();
  	expect(qsize1 instanceof qt.QSize).to.equal(true);
  	const qsize2 = new qt.QSize(1, 2);
  	expect(qsize2.width).to.equal(1);
  	expect(qsize2.height).to.equal(2);
  	const qsize3 = new qt.QSize(qsize2);
  	expect(qsize3.width).to.equal(1);
  	expect(qsize3.height).to.equal(2);
  });
  it('should create QSize with function', () => {
  	const qsize1 = qt.QSize();
  	expect(qsize1 instanceof qt.QSize).to.equal(true);
  	const qsize2 = qt.QSize(1, 2);
  	expect(qsize2.width).to.equal(1);
  	expect(qsize2.height).to.equal(2);
  	const qsize3 = qt.QSize(qsize2);
  	expect(qsize3.width).to.equal(1);
  	expect(qsize3.height).to.equal(2);
  });
  it('should test width/height set/get', () => {
  	const qsize = new qt.QSize(11, 13);
  	expect(qsize.width).to.equal(11);
  	expect(qsize.height).to.equal(13);
  	qsize.width = 17;
  	qsize.height = 19;
  	expect(qsize.width).to.equal(17);
  	expect(qsize.height).to.equal(19);
  });
  it('should test isEmpty, isNull, isValid', () => {
  	const qsize1 = new qt.QSize();
  	expect(qsize1.isValid()).to.equal(false);
  	expect(qsize1.isEmpty()).to.equal(true);
  	expect(qsize1.isNull()).to.equal(false);
  	const qsize2 = new qt.QSize(11, 13);
  	expect(qsize2.isValid()).to.equal(true);
  	expect(qsize2.isEmpty()).to.equal(false);
  	qsize2.width = qsize2.height = 0;
  	expect(qsize2.isNull()).to.equal(true);
  });
});