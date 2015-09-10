var should = require('chai').should();
var ritz = require('../build/Release/ritz');

describe('Ritz', () => {
  describe('.init()', () => {
    it('should have a function named createServer', () => {
      ritz.createServer.should.be.a('function');
    });
  });
});
