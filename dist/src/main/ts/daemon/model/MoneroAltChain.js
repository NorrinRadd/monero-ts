"use strict";Object.defineProperty(exports, "__esModule", { value: true });exports.default = void 0; /**
 * Models an alternative chain seen by the node.
 */
class MoneroAltChain {







  constructor(altChain) {
    Object.assign(this, altChain);
    if (this.difficulty !== undefined && typeof this.difficulty !== "bigint") this.difficulty = BigInt(this.difficulty);
  }

  toJson() {
    let json = Object.assign({}, this);
    if (this.getDifficulty() !== undefined) json.difficulty = this.getDifficulty().toString();
    return json;
  }

  getBlockHashes() {
    return this.blockHashes;
  }

  setBlockHashes(blockHashes) {
    this.blockHashes = blockHashes;
    return this;
  }

  getDifficulty() {
    return this.difficulty;
  }

  setDifficulty(difficulty) {
    this.difficulty = difficulty;
    return this;
  }

  getHeight() {
    return this.height;
  }

  setHeight(height) {
    this.height = height;
    return this;
  }

  getLength() {
    return this.length;
  }

  setLength(length) {
    this.length = length;
    return this;
  }

  getMainChainParentBlockHash() {
    return this.mainChainParentBlockHash;
  }

  setMainChainParentBlockHash(mainChainParentBlockHash) {
    this.mainChainParentBlockHash = mainChainParentBlockHash;
    return this;
  }
}exports.default = MoneroAltChain;
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJuYW1lcyI6WyJNb25lcm9BbHRDaGFpbiIsImNvbnN0cnVjdG9yIiwiYWx0Q2hhaW4iLCJPYmplY3QiLCJhc3NpZ24iLCJkaWZmaWN1bHR5IiwidW5kZWZpbmVkIiwiQmlnSW50IiwidG9Kc29uIiwianNvbiIsImdldERpZmZpY3VsdHkiLCJ0b1N0cmluZyIsImdldEJsb2NrSGFzaGVzIiwiYmxvY2tIYXNoZXMiLCJzZXRCbG9ja0hhc2hlcyIsInNldERpZmZpY3VsdHkiLCJnZXRIZWlnaHQiLCJoZWlnaHQiLCJzZXRIZWlnaHQiLCJnZXRMZW5ndGgiLCJsZW5ndGgiLCJzZXRMZW5ndGgiLCJnZXRNYWluQ2hhaW5QYXJlbnRCbG9ja0hhc2giLCJtYWluQ2hhaW5QYXJlbnRCbG9ja0hhc2giLCJzZXRNYWluQ2hhaW5QYXJlbnRCbG9ja0hhc2giLCJleHBvcnRzIiwiZGVmYXVsdCJdLCJzb3VyY2VzIjpbIi4uLy4uLy4uLy4uLy4uLy4uL3NyYy9tYWluL3RzL2RhZW1vbi9tb2RlbC9Nb25lcm9BbHRDaGFpbi50cyJdLCJzb3VyY2VzQ29udGVudCI6WyIvKipcbiAqIE1vZGVscyBhbiBhbHRlcm5hdGl2ZSBjaGFpbiBzZWVuIGJ5IHRoZSBub2RlLlxuICovXG5leHBvcnQgZGVmYXVsdCBjbGFzcyBNb25lcm9BbHRDaGFpbiB7XG5cbiAgYmxvY2tIYXNoZXM6IHN0cmluZ1tdO1xuICBkaWZmaWN1bHR5OiBiaWdpbnQ7XG4gIGhlaWdodDogbnVtYmVyO1xuICBsZW5ndGg6IG51bWJlcjtcbiAgbWFpbkNoYWluUGFyZW50QmxvY2tIYXNoOiBzdHJpbmc7XG4gIFxuICBjb25zdHJ1Y3RvcihhbHRDaGFpbj86IFBhcnRpYWw8TW9uZXJvQWx0Q2hhaW4+KSB7XG4gICAgT2JqZWN0LmFzc2lnbih0aGlzLCBhbHRDaGFpbik7XG4gICAgaWYgKHRoaXMuZGlmZmljdWx0eSAhPT0gdW5kZWZpbmVkICYmIHR5cGVvZiB0aGlzLmRpZmZpY3VsdHkgIT09IFwiYmlnaW50XCIpIHRoaXMuZGlmZmljdWx0eSA9IEJpZ0ludCh0aGlzLmRpZmZpY3VsdHkpO1xuICB9XG4gIFxuICB0b0pzb24oKTogYW55IHtcbiAgICBsZXQganNvbjogYW55ID0gT2JqZWN0LmFzc2lnbih7fSwgdGhpcyk7XG4gICAgaWYgKHRoaXMuZ2V0RGlmZmljdWx0eSgpICE9PSB1bmRlZmluZWQpIGpzb24uZGlmZmljdWx0eSA9IHRoaXMuZ2V0RGlmZmljdWx0eSgpLnRvU3RyaW5nKCk7XG4gICAgcmV0dXJuIGpzb247XG4gIH1cbiAgXG4gIGdldEJsb2NrSGFzaGVzKCk6IHN0cmluZ1tdIHtcbiAgICByZXR1cm4gdGhpcy5ibG9ja0hhc2hlcztcbiAgfVxuICBcbiAgc2V0QmxvY2tIYXNoZXMoYmxvY2tIYXNoZXM6IHN0cmluZ1tdKTogTW9uZXJvQWx0Q2hhaW4ge1xuICAgIHRoaXMuYmxvY2tIYXNoZXMgPSBibG9ja0hhc2hlcztcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuICBcbiAgZ2V0RGlmZmljdWx0eSgpOiBiaWdpbnQge1xuICAgIHJldHVybiB0aGlzLmRpZmZpY3VsdHk7XG4gIH1cbiAgXG4gIHNldERpZmZpY3VsdHkoZGlmZmljdWx0eTogYmlnaW50KTogTW9uZXJvQWx0Q2hhaW4ge1xuICAgIHRoaXMuZGlmZmljdWx0eSA9IGRpZmZpY3VsdHk7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cbiAgXG4gIGdldEhlaWdodCgpOiBudW1iZXIge1xuICAgIHJldHVybiB0aGlzLmhlaWdodDtcbiAgfVxuICBcbiAgc2V0SGVpZ2h0KGhlaWdodDogbnVtYmVyKTogTW9uZXJvQWx0Q2hhaW4ge1xuICAgIHRoaXMuaGVpZ2h0ID0gaGVpZ2h0O1xuICAgIHJldHVybiB0aGlzO1xuICB9XG4gIFxuICBnZXRMZW5ndGgoKTogbnVtYmVyIHtcbiAgICByZXR1cm4gdGhpcy5sZW5ndGg7XG4gIH1cbiAgXG4gIHNldExlbmd0aChsZW5ndGg6IG51bWJlcik6IE1vbmVyb0FsdENoYWluIHtcbiAgICB0aGlzLmxlbmd0aCA9IGxlbmd0aDtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuICBcbiAgZ2V0TWFpbkNoYWluUGFyZW50QmxvY2tIYXNoKCk6IHN0cmluZyB7XG4gICAgcmV0dXJuIHRoaXMubWFpbkNoYWluUGFyZW50QmxvY2tIYXNoO1xuICB9XG4gIFxuICBzZXRNYWluQ2hhaW5QYXJlbnRCbG9ja0hhc2gobWFpbkNoYWluUGFyZW50QmxvY2tIYXNoOiBzdHJpbmcpOiBNb25lcm9BbHRDaGFpbiB7XG4gICAgdGhpcy5tYWluQ2hhaW5QYXJlbnRCbG9ja0hhc2ggPSBtYWluQ2hhaW5QYXJlbnRCbG9ja0hhc2g7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cbn1cbiJdLCJtYXBwaW5ncyI6InFHQUFBO0FBQ0E7QUFDQTtBQUNlLE1BQU1BLGNBQWMsQ0FBQzs7Ozs7Ozs7RUFRbENDLFdBQVdBLENBQUNDLFFBQWtDLEVBQUU7SUFDOUNDLE1BQU0sQ0FBQ0MsTUFBTSxDQUFDLElBQUksRUFBRUYsUUFBUSxDQUFDO0lBQzdCLElBQUksSUFBSSxDQUFDRyxVQUFVLEtBQUtDLFNBQVMsSUFBSSxPQUFPLElBQUksQ0FBQ0QsVUFBVSxLQUFLLFFBQVEsRUFBRSxJQUFJLENBQUNBLFVBQVUsR0FBR0UsTUFBTSxDQUFDLElBQUksQ0FBQ0YsVUFBVSxDQUFDO0VBQ3JIOztFQUVBRyxNQUFNQSxDQUFBLEVBQVE7SUFDWixJQUFJQyxJQUFTLEdBQUdOLE1BQU0sQ0FBQ0MsTUFBTSxDQUFDLENBQUMsQ0FBQyxFQUFFLElBQUksQ0FBQztJQUN2QyxJQUFJLElBQUksQ0FBQ00sYUFBYSxDQUFDLENBQUMsS0FBS0osU0FBUyxFQUFFRyxJQUFJLENBQUNKLFVBQVUsR0FBRyxJQUFJLENBQUNLLGFBQWEsQ0FBQyxDQUFDLENBQUNDLFFBQVEsQ0FBQyxDQUFDO0lBQ3pGLE9BQU9GLElBQUk7RUFDYjs7RUFFQUcsY0FBY0EsQ0FBQSxFQUFhO0lBQ3pCLE9BQU8sSUFBSSxDQUFDQyxXQUFXO0VBQ3pCOztFQUVBQyxjQUFjQSxDQUFDRCxXQUFxQixFQUFrQjtJQUNwRCxJQUFJLENBQUNBLFdBQVcsR0FBR0EsV0FBVztJQUM5QixPQUFPLElBQUk7RUFDYjs7RUFFQUgsYUFBYUEsQ0FBQSxFQUFXO0lBQ3RCLE9BQU8sSUFBSSxDQUFDTCxVQUFVO0VBQ3hCOztFQUVBVSxhQUFhQSxDQUFDVixVQUFrQixFQUFrQjtJQUNoRCxJQUFJLENBQUNBLFVBQVUsR0FBR0EsVUFBVTtJQUM1QixPQUFPLElBQUk7RUFDYjs7RUFFQVcsU0FBU0EsQ0FBQSxFQUFXO0lBQ2xCLE9BQU8sSUFBSSxDQUFDQyxNQUFNO0VBQ3BCOztFQUVBQyxTQUFTQSxDQUFDRCxNQUFjLEVBQWtCO0lBQ3hDLElBQUksQ0FBQ0EsTUFBTSxHQUFHQSxNQUFNO0lBQ3BCLE9BQU8sSUFBSTtFQUNiOztFQUVBRSxTQUFTQSxDQUFBLEVBQVc7SUFDbEIsT0FBTyxJQUFJLENBQUNDLE1BQU07RUFDcEI7O0VBRUFDLFNBQVNBLENBQUNELE1BQWMsRUFBa0I7SUFDeEMsSUFBSSxDQUFDQSxNQUFNLEdBQUdBLE1BQU07SUFDcEIsT0FBTyxJQUFJO0VBQ2I7O0VBRUFFLDJCQUEyQkEsQ0FBQSxFQUFXO0lBQ3BDLE9BQU8sSUFBSSxDQUFDQyx3QkFBd0I7RUFDdEM7O0VBRUFDLDJCQUEyQkEsQ0FBQ0Qsd0JBQWdDLEVBQWtCO0lBQzVFLElBQUksQ0FBQ0Esd0JBQXdCLEdBQUdBLHdCQUF3QjtJQUN4RCxPQUFPLElBQUk7RUFDYjtBQUNGLENBQUNFLE9BQUEsQ0FBQUMsT0FBQSxHQUFBMUIsY0FBQSJ9