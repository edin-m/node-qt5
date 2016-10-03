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
  	const qsize = qt.QSize(11, 13);
  	expect(qsize.width).to.equal(11);
  	expect(qsize.height).to.equal(13);
  	qsize.width = 17;
  	qsize.height = 19;
  	expect(qsize.width).to.equal(17);
  	expect(qsize.height).to.equal(19);
  });
  it('should test isEmpty(), isNull(), isValid()', () => {
  	const qsize1 = qt.QSize();
  	expect(qsize1.isValid()).to.equal(false);
  	expect(qsize1.isEmpty()).to.equal(true);
  	expect(qsize1.isNull()).to.equal(false);
  	const qsize2 = qt.QSize(11, 13);
  	expect(qsize2.isValid()).to.equal(true);
  	expect(qsize2.isEmpty()).to.equal(false);
  	qsize2.width = qsize2.height = 0;
  	expect(qsize2.isNull()).to.equal(true);
  });
  it('should test scale()', () => {
  	const qsize1 = qt.QSize(10, 12);
  	qsize1.scale(60, 60, qt.Qt.AspectRatioMode.IgnoreAspectRatio);
  	expect(qsize1.width).to.equal(60);
  	expect(qsize1.height).to.equal(60);
  	const qsize2 = qt.QSize(10, 12);
  	qsize2.scale(60, 60, qt.Qt.AspectRatioMode.KeepAspectRatio);
  	expect(qsize2.width).to.equal(50);
  	expect(qsize2.height).to.equal(60);
  	const qsize3 = qt.QSize(10, 12);
  	qsize3.scale(60, 60, qt.Qt.AspectRatioMode.KeepAspectRatioByExpanding);
  	expect(qsize3.width).to.equal(60);
  	expect(qsize3.height).to.equal(72);
  	// TODO: scale with QSize as argument
  });
  it('should test scaled()', () => {
  	const qsize1 = qt.QSize(10, 12).scaled(60, 60, qt.Qt.AspectRatioMode.IgnoreAspectRatio);
  	expect(qsize1.width).to.equal(60);
  	expect(qsize1.height).to.equal(60);
  	const qsize2 = qt.QSize(10, 12).scaled(60, 60, qt.Qt.AspectRatioMode.KeepAspectRatio);
  	expect(qsize2.width).to.equal(50);
  	expect(qsize2.height).to.equal(60);
  	const qsize3 = qt.QSize(10, 12).scaled(60, 60, qt.Qt.AspectRatioMode.KeepAspectRatioByExpanding);
  	expect(qsize3.width).to.equal(60);
  	expect(qsize3.height).to.equal(72);
  	// TODO: scaled with QSize as argument
  });
  it('should test transpose/transposed()', () => {
  	const qsize1 = qt.QSize(11, 13);
  	qsize1.transpose();
  	expect(qsize1.width).to.equal(13);
  	expect(qsize1.height).to.equal(11);
  	const qsize2 = qsize1.transposed();
  	expect(qsize2.width).to.equal(11);
  	expect(qsize2.height).to.equal(13);
  });
  it('should test multiply operator', () => {
  	const qsize1 = qt.QSize(11, 13);
  	const qsize2 = qsize1.multiply(3);
  	expect(qsize1.width).to.equal(qsize2.width);
  	expect(qsize1.height).to.equal(qsize2.height);
  	expect(qsize1.width).to.equal(33);
  	expect(qsize1.height).to.equal(39);
  });
  it('should test plus operator', () => {
  	const s = qt.QSize(3, 7);
  	const r = qt.QSize(-1, 4);
  	s.plus(r);
  	expect(s.width).to.equal(2);
  	expect(s.height).to.equal(11);
  });
  it('should test minus operator', () => {
  	const s = qt.QSize(3, 7);
  	const r = qt.QSize(-1, 4);
  	s.minus(r);
  	expect(s.width).to.equal(4);
  	expect(s.height).to.equal(3);
  });
  it('should test divide operator', () => {
  	const qsize1 = qt.QSize(33, 39);
  	const qsize2 = qsize1.divide(3);
  	expect(qsize1.width).to.equal(qsize2.width);
  	expect(qsize1.height).to.equal(qsize2.height);
  	expect(qsize1.width).to.equal(11);
  	expect(qsize1.height).to.equal(13);
  });
});
