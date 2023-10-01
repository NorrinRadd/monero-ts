"use strict";var _interopRequireDefault = require("@babel/runtime/helpers/interopRequireDefault");Object.defineProperty(exports, "__esModule", { value: true });exports.default = void 0;var _assert = _interopRequireDefault(require("assert"));
var _GenUtils = _interopRequireDefault(require("../../common/GenUtils"));


/**
 * Models a Monero key image.
 */
class MoneroKeyImage {




  /**
   * Construct the model.
   * 
   * @param {string|Partial<MoneroKeyImage>} [keyImageOrHex] is a MoneroKeyImage or hex string to initialize from (optional)
   * @param {string} [signature] is the key image's signature
   */
  constructor(hexOrKeyImage, signature) {
    if (typeof hexOrKeyImage === "string") {
      this.setHex(hexOrKeyImage);
      this.setSignature(signature);
    } else {
      Object.assign(this, hexOrKeyImage);
    }
  }

  getHex() {
    return this.hex;
  }

  setHex(hex) {
    this.hex = hex;
    return this;
  }

  getSignature() {
    return this.signature;
  }

  setSignature(signature) {
    this.signature = signature;
    return this;
  }

  copy() {
    return new MoneroKeyImage(this);
  }

  toJson() {
    return Object.assign({}, this);
  }

  merge(keyImage) {
    (0, _assert.default)(keyImage instanceof MoneroKeyImage);
    if (keyImage === this) return this;
    this.setHex(_GenUtils.default.reconcile(this.getHex(), keyImage.getHex()));
    this.setSignature(_GenUtils.default.reconcile(this.getSignature(), keyImage.getSignature()));
    return this;
  }

  toString(indent = 0) {
    let str = "";
    str += _GenUtils.default.kvLine("Hex", this.getHex(), indent);
    str += _GenUtils.default.kvLine("Signature", this.getSignature(), indent);
    return str.slice(0, str.length - 1); // strip last newline
  }
}exports.default = MoneroKeyImage;
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJuYW1lcyI6WyJfYXNzZXJ0IiwiX2ludGVyb3BSZXF1aXJlRGVmYXVsdCIsInJlcXVpcmUiLCJfR2VuVXRpbHMiLCJNb25lcm9LZXlJbWFnZSIsImNvbnN0cnVjdG9yIiwiaGV4T3JLZXlJbWFnZSIsInNpZ25hdHVyZSIsInNldEhleCIsInNldFNpZ25hdHVyZSIsIk9iamVjdCIsImFzc2lnbiIsImdldEhleCIsImhleCIsImdldFNpZ25hdHVyZSIsImNvcHkiLCJ0b0pzb24iLCJtZXJnZSIsImtleUltYWdlIiwiYXNzZXJ0IiwiR2VuVXRpbHMiLCJyZWNvbmNpbGUiLCJ0b1N0cmluZyIsImluZGVudCIsInN0ciIsImt2TGluZSIsInNsaWNlIiwibGVuZ3RoIiwiZXhwb3J0cyIsImRlZmF1bHQiXSwic291cmNlcyI6WyIuLi8uLi8uLi8uLi8uLi8uLi9zcmMvbWFpbi90cy9kYWVtb24vbW9kZWwvTW9uZXJvS2V5SW1hZ2UudHMiXSwic291cmNlc0NvbnRlbnQiOlsiaW1wb3J0IGFzc2VydCBmcm9tIFwiYXNzZXJ0XCI7XG5pbXBvcnQgR2VuVXRpbHMgZnJvbSBcIi4uLy4uL2NvbW1vbi9HZW5VdGlsc1wiO1xuaW1wb3J0IE1vbmVyb0Vycm9yIGZyb20gXCIuLi8uLi9jb21tb24vTW9uZXJvRXJyb3JcIjtcblxuLyoqXG4gKiBNb2RlbHMgYSBNb25lcm8ga2V5IGltYWdlLlxuICovXG5leHBvcnQgZGVmYXVsdCBjbGFzcyBNb25lcm9LZXlJbWFnZSB7XG4gIFxuICBoZXg6IHN0cmluZztcbiAgc2lnbmF0dXJlOiBzdHJpbmc7XG4gIFxuICAvKipcbiAgICogQ29uc3RydWN0IHRoZSBtb2RlbC5cbiAgICogXG4gICAqIEBwYXJhbSB7c3RyaW5nfFBhcnRpYWw8TW9uZXJvS2V5SW1hZ2U+fSBba2V5SW1hZ2VPckhleF0gaXMgYSBNb25lcm9LZXlJbWFnZSBvciBoZXggc3RyaW5nIHRvIGluaXRpYWxpemUgZnJvbSAob3B0aW9uYWwpXG4gICAqIEBwYXJhbSB7c3RyaW5nfSBbc2lnbmF0dXJlXSBpcyB0aGUga2V5IGltYWdlJ3Mgc2lnbmF0dXJlXG4gICAqL1xuICBjb25zdHJ1Y3RvcihoZXhPcktleUltYWdlPzogc3RyaW5nIHwgUGFydGlhbDxNb25lcm9LZXlJbWFnZT4sIHNpZ25hdHVyZT86IHN0cmluZykge1xuICAgIGlmICh0eXBlb2YgaGV4T3JLZXlJbWFnZSA9PT0gXCJzdHJpbmdcIikge1xuICAgICAgdGhpcy5zZXRIZXgoaGV4T3JLZXlJbWFnZSk7XG4gICAgICB0aGlzLnNldFNpZ25hdHVyZShzaWduYXR1cmUpO1xuICAgIH0gZWxzZSB7XG4gICAgICBPYmplY3QuYXNzaWduKHRoaXMsIGhleE9yS2V5SW1hZ2UpO1xuICAgIH1cbiAgfVxuXG4gIGdldEhleCgpOiBzdHJpbmcge1xuICAgIHJldHVybiB0aGlzLmhleDtcbiAgfVxuXG4gIHNldEhleChoZXg6IHN0cmluZyk6IE1vbmVyb0tleUltYWdlIHtcbiAgICB0aGlzLmhleCA9IGhleDtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIGdldFNpZ25hdHVyZSgpOiBzdHJpbmcge1xuICAgIHJldHVybiB0aGlzLnNpZ25hdHVyZTtcbiAgfVxuXG4gIHNldFNpZ25hdHVyZShzaWduYXR1cmU6IHN0cmluZyk6IE1vbmVyb0tleUltYWdlIHtcbiAgICB0aGlzLnNpZ25hdHVyZSA9IHNpZ25hdHVyZTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuICBcbiAgY29weSgpOiBNb25lcm9LZXlJbWFnZSB7XG4gICAgcmV0dXJuIG5ldyBNb25lcm9LZXlJbWFnZSh0aGlzKTtcbiAgfVxuICBcbiAgdG9Kc29uKCkge1xuICAgIHJldHVybiBPYmplY3QuYXNzaWduKHt9LCB0aGlzKTtcbiAgfVxuICBcbiAgbWVyZ2Uoa2V5SW1hZ2U6IE1vbmVyb0tleUltYWdlKTogTW9uZXJvS2V5SW1hZ2Uge1xuICAgIGFzc2VydChrZXlJbWFnZSBpbnN0YW5jZW9mIE1vbmVyb0tleUltYWdlKTtcbiAgICBpZiAoa2V5SW1hZ2UgPT09IHRoaXMpIHJldHVybiB0aGlzO1xuICAgIHRoaXMuc2V0SGV4KEdlblV0aWxzLnJlY29uY2lsZSh0aGlzLmdldEhleCgpLCBrZXlJbWFnZS5nZXRIZXgoKSkpO1xuICAgIHRoaXMuc2V0U2lnbmF0dXJlKEdlblV0aWxzLnJlY29uY2lsZSh0aGlzLmdldFNpZ25hdHVyZSgpLCBrZXlJbWFnZS5nZXRTaWduYXR1cmUoKSkpO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG4gIFxuICB0b1N0cmluZyhpbmRlbnQgPSAwKTogc3RyaW5nIHtcbiAgICBsZXQgc3RyID0gXCJcIjtcbiAgICBzdHIgKz0gR2VuVXRpbHMua3ZMaW5lKFwiSGV4XCIsIHRoaXMuZ2V0SGV4KCksIGluZGVudCk7XG4gICAgc3RyICs9IEdlblV0aWxzLmt2TGluZShcIlNpZ25hdHVyZVwiLCB0aGlzLmdldFNpZ25hdHVyZSgpLCBpbmRlbnQpO1xuICAgIHJldHVybiBzdHIuc2xpY2UoMCwgc3RyLmxlbmd0aCAtIDEpOyAgLy8gc3RyaXAgbGFzdCBuZXdsaW5lXG4gIH1cbn1cbiJdLCJtYXBwaW5ncyI6InlMQUFBLElBQUFBLE9BQUEsR0FBQUMsc0JBQUEsQ0FBQUMsT0FBQTtBQUNBLElBQUFDLFNBQUEsR0FBQUYsc0JBQUEsQ0FBQUMsT0FBQTs7O0FBR0E7QUFDQTtBQUNBO0FBQ2UsTUFBTUUsY0FBYyxDQUFDOzs7OztFQUtsQztBQUNGO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7RUFDRUMsV0FBV0EsQ0FBQ0MsYUFBZ0QsRUFBRUMsU0FBa0IsRUFBRTtJQUNoRixJQUFJLE9BQU9ELGFBQWEsS0FBSyxRQUFRLEVBQUU7TUFDckMsSUFBSSxDQUFDRSxNQUFNLENBQUNGLGFBQWEsQ0FBQztNQUMxQixJQUFJLENBQUNHLFlBQVksQ0FBQ0YsU0FBUyxDQUFDO0lBQzlCLENBQUMsTUFBTTtNQUNMRyxNQUFNLENBQUNDLE1BQU0sQ0FBQyxJQUFJLEVBQUVMLGFBQWEsQ0FBQztJQUNwQztFQUNGOztFQUVBTSxNQUFNQSxDQUFBLEVBQVc7SUFDZixPQUFPLElBQUksQ0FBQ0MsR0FBRztFQUNqQjs7RUFFQUwsTUFBTUEsQ0FBQ0ssR0FBVyxFQUFrQjtJQUNsQyxJQUFJLENBQUNBLEdBQUcsR0FBR0EsR0FBRztJQUNkLE9BQU8sSUFBSTtFQUNiOztFQUVBQyxZQUFZQSxDQUFBLEVBQVc7SUFDckIsT0FBTyxJQUFJLENBQUNQLFNBQVM7RUFDdkI7O0VBRUFFLFlBQVlBLENBQUNGLFNBQWlCLEVBQWtCO0lBQzlDLElBQUksQ0FBQ0EsU0FBUyxHQUFHQSxTQUFTO0lBQzFCLE9BQU8sSUFBSTtFQUNiOztFQUVBUSxJQUFJQSxDQUFBLEVBQW1CO0lBQ3JCLE9BQU8sSUFBSVgsY0FBYyxDQUFDLElBQUksQ0FBQztFQUNqQzs7RUFFQVksTUFBTUEsQ0FBQSxFQUFHO0lBQ1AsT0FBT04sTUFBTSxDQUFDQyxNQUFNLENBQUMsQ0FBQyxDQUFDLEVBQUUsSUFBSSxDQUFDO0VBQ2hDOztFQUVBTSxLQUFLQSxDQUFDQyxRQUF3QixFQUFrQjtJQUM5QyxJQUFBQyxlQUFNLEVBQUNELFFBQVEsWUFBWWQsY0FBYyxDQUFDO0lBQzFDLElBQUljLFFBQVEsS0FBSyxJQUFJLEVBQUUsT0FBTyxJQUFJO0lBQ2xDLElBQUksQ0FBQ1YsTUFBTSxDQUFDWSxpQkFBUSxDQUFDQyxTQUFTLENBQUMsSUFBSSxDQUFDVCxNQUFNLENBQUMsQ0FBQyxFQUFFTSxRQUFRLENBQUNOLE1BQU0sQ0FBQyxDQUFDLENBQUMsQ0FBQztJQUNqRSxJQUFJLENBQUNILFlBQVksQ0FBQ1csaUJBQVEsQ0FBQ0MsU0FBUyxDQUFDLElBQUksQ0FBQ1AsWUFBWSxDQUFDLENBQUMsRUFBRUksUUFBUSxDQUFDSixZQUFZLENBQUMsQ0FBQyxDQUFDLENBQUM7SUFDbkYsT0FBTyxJQUFJO0VBQ2I7O0VBRUFRLFFBQVFBLENBQUNDLE1BQU0sR0FBRyxDQUFDLEVBQVU7SUFDM0IsSUFBSUMsR0FBRyxHQUFHLEVBQUU7SUFDWkEsR0FBRyxJQUFJSixpQkFBUSxDQUFDSyxNQUFNLENBQUMsS0FBSyxFQUFFLElBQUksQ0FBQ2IsTUFBTSxDQUFDLENBQUMsRUFBRVcsTUFBTSxDQUFDO0lBQ3BEQyxHQUFHLElBQUlKLGlCQUFRLENBQUNLLE1BQU0sQ0FBQyxXQUFXLEVBQUUsSUFBSSxDQUFDWCxZQUFZLENBQUMsQ0FBQyxFQUFFUyxNQUFNLENBQUM7SUFDaEUsT0FBT0MsR0FBRyxDQUFDRSxLQUFLLENBQUMsQ0FBQyxFQUFFRixHQUFHLENBQUNHLE1BQU0sR0FBRyxDQUFDLENBQUMsQ0FBQyxDQUFFO0VBQ3hDO0FBQ0YsQ0FBQ0MsT0FBQSxDQUFBQyxPQUFBLEdBQUF6QixjQUFBIn0=