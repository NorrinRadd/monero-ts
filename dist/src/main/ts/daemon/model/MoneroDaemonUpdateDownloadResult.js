"use strict";var _interopRequireDefault = require("@babel/runtime/helpers/interopRequireDefault");Object.defineProperty(exports, "__esModule", { value: true });exports.default = void 0;var _MoneroDaemonUpdateCheckResult = _interopRequireDefault(require("./MoneroDaemonUpdateCheckResult"));

/**
 * Models the result of downloading an update.
 */
class MoneroDaemonUpdateDownloadResult extends _MoneroDaemonUpdateCheckResult.default {



  constructor(state) {
    super(state);
  }

  /**
   * Get the path the update was downloaded to.
   * 
   * @return {string} is the path the update was downloaded to
   */
  getDownloadPath() {
    return this.downloadPath;
  }

  setDownloadPath(downloadPath) {
    this.downloadPath = downloadPath;
    return this;
  }
}exports.default = MoneroDaemonUpdateDownloadResult;
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJuYW1lcyI6WyJfTW9uZXJvRGFlbW9uVXBkYXRlQ2hlY2tSZXN1bHQiLCJfaW50ZXJvcFJlcXVpcmVEZWZhdWx0IiwicmVxdWlyZSIsIk1vbmVyb0RhZW1vblVwZGF0ZURvd25sb2FkUmVzdWx0IiwiTW9uZXJvRGFlbW9uVXBkYXRlQ2hlY2tSZXN1bHQiLCJjb25zdHJ1Y3RvciIsInN0YXRlIiwiZ2V0RG93bmxvYWRQYXRoIiwiZG93bmxvYWRQYXRoIiwic2V0RG93bmxvYWRQYXRoIiwiZXhwb3J0cyIsImRlZmF1bHQiXSwic291cmNlcyI6WyIuLi8uLi8uLi8uLi8uLi8uLi9zcmMvbWFpbi90cy9kYWVtb24vbW9kZWwvTW9uZXJvRGFlbW9uVXBkYXRlRG93bmxvYWRSZXN1bHQudHMiXSwic291cmNlc0NvbnRlbnQiOlsiaW1wb3J0IE1vbmVyb0RhZW1vblVwZGF0ZUNoZWNrUmVzdWx0IGZyb20gXCIuL01vbmVyb0RhZW1vblVwZGF0ZUNoZWNrUmVzdWx0XCI7XG5cbi8qKlxuICogTW9kZWxzIHRoZSByZXN1bHQgb2YgZG93bmxvYWRpbmcgYW4gdXBkYXRlLlxuICovXG5leHBvcnQgZGVmYXVsdCBjbGFzcyBNb25lcm9EYWVtb25VcGRhdGVEb3dubG9hZFJlc3VsdCBleHRlbmRzIE1vbmVyb0RhZW1vblVwZGF0ZUNoZWNrUmVzdWx0IHtcblxuICBkb3dubG9hZFBhdGg6IHN0cmluZztcbiAgXG4gIGNvbnN0cnVjdG9yKHN0YXRlOiBNb25lcm9EYWVtb25VcGRhdGVEb3dubG9hZFJlc3VsdCkge1xuICAgIHN1cGVyKHN0YXRlKTtcbiAgfVxuICBcbiAgLyoqXG4gICAqIEdldCB0aGUgcGF0aCB0aGUgdXBkYXRlIHdhcyBkb3dubG9hZGVkIHRvLlxuICAgKiBcbiAgICogQHJldHVybiB7c3RyaW5nfSBpcyB0aGUgcGF0aCB0aGUgdXBkYXRlIHdhcyBkb3dubG9hZGVkIHRvXG4gICAqL1xuICBnZXREb3dubG9hZFBhdGgoKTogc3RyaW5nIHtcbiAgICByZXR1cm4gdGhpcy5kb3dubG9hZFBhdGg7XG4gIH1cbiAgXG4gIHNldERvd25sb2FkUGF0aChkb3dubG9hZFBhdGg6IHN0cmluZyk6IE1vbmVyb0RhZW1vblVwZGF0ZURvd25sb2FkUmVzdWx0IHtcbiAgICB0aGlzLmRvd25sb2FkUGF0aCA9IGRvd25sb2FkUGF0aDtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxufSJdLCJtYXBwaW5ncyI6InlMQUFBLElBQUFBLDhCQUFBLEdBQUFDLHNCQUFBLENBQUFDLE9BQUE7O0FBRUE7QUFDQTtBQUNBO0FBQ2UsTUFBTUMsZ0NBQWdDLFNBQVNDLHNDQUE2QixDQUFDOzs7O0VBSTFGQyxXQUFXQSxDQUFDQyxLQUF1QyxFQUFFO0lBQ25ELEtBQUssQ0FBQ0EsS0FBSyxDQUFDO0VBQ2Q7O0VBRUE7QUFDRjtBQUNBO0FBQ0E7QUFDQTtFQUNFQyxlQUFlQSxDQUFBLEVBQVc7SUFDeEIsT0FBTyxJQUFJLENBQUNDLFlBQVk7RUFDMUI7O0VBRUFDLGVBQWVBLENBQUNELFlBQW9CLEVBQW9DO0lBQ3RFLElBQUksQ0FBQ0EsWUFBWSxHQUFHQSxZQUFZO0lBQ2hDLE9BQU8sSUFBSTtFQUNiO0FBQ0YsQ0FBQ0UsT0FBQSxDQUFBQyxPQUFBLEdBQUFSLGdDQUFBIn0=