var should = require('chai').should();
var ritz = require('../build/Release/ritz');

describe('Ritz', () => {
  describe('.createServer()', () => {
    it('should exist', () => {
      should.exist(ritz.createServer);
      ritz.createServer.should.be.an.instanceOf(Function);
    });
    it('should not throw exceptions', () => {
      ritz.createServer.should.not.throw(Error);
    });
  });
});
