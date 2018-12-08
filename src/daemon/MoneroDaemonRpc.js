const assert = require("assert");
const MoneroUtils = require("../utils/MoneroUtils");
const MoneroRpc = require("../rpc/MoneroRpc")
const MoneroDaemon = require("./MoneroDaemon");
const MoneroDaemonResponseInfo = require("./model/MoneroDaemonResponseInfo"); 
const MoneroHeight = require("./model/MoneroHeight");
const MoneroBlockHeader = require("./model/MoneroBlockHeader");
const MoneroBlock = require("./model/MoneroBlock");
const MoneroTx = require("./model/MoneroTx");
const MoneroBlockTemplate = require("./model/MoneroBlockTemplate");
const MoneroDaemonInfo = require("./model/MoneroDaemonInfo");
const BigInteger = require("../submodules/mymonero-core-js/cryptonote_utils/biginteger").BigInteger;

/**
 * Implements a Monero daemon using monero-daemon-rpc.
 */
class MoneroDaemonRpc extends MoneroDaemon {
  
  /**
   * Constructs the daemon.
   * 
   * @param config is the daemon configuration	// TODO: config default and validation
   */
  constructor(config) {
    super();
    
    // assign config
    this.config = Object.assign({}, config);
    
    // initialize rpc if not given
    if (!this.config.rpc) this.config.rpc = new MoneroRpc(config);
    
    // one time initialization
    this.initPromise = this._initOneTime();
  }
  
  async getHeight() {
    await this._initOneTime();
    return (await this.config.rpc.sendJsonRpcRequest("get_block_count")).count;
  }
  
  async getBlockHash(height) {
    await this._initOneTime();
    return await this.config.rpc.sendJsonRpcRequest("on_get_block_hash", [height]);
  }
  
  async getBlockTemplate(walletAddress, reserveSize) {
    await this._initOneTime();
    let resp = await this.config.rpc.sendJsonRpcRequest("get_block_template", { wallet_address: walletAddress, reserve_size: reserveSize });
    let template = MoneroDaemonRpc._buildBlockTemplate(resp);
    MoneroDaemonRpc._setResponseInfo(resp, template);
    return template;
  }
  
  async getLastBlockHeader() {
    await this._initOneTime();
    let resp = await this.config.rpc.sendJsonRpcRequest("get_last_block_header");
    let header = MoneroDaemonRpc._buildBlockHeader(resp.block_header);
    MoneroDaemonRpc._setResponseInfo(resp, header);
    return header;
  }
  
  async getBlockHeaderByHash(hash) {
    await this._initOneTime();
    let resp = await this.config.rpc.sendJsonRpcRequest("get_block_header_by_hash", { hash: hash } );
    let header = MoneroDaemonRpc._buildBlockHeader(resp.block_header);
    MoneroDaemonRpc._setResponseInfo(resp, header);
    return header;
  }
  
  async getBlockHeaderByHeight(height) {
    await this._initOneTime();
    let resp = await this.config.rpc.sendJsonRpcRequest("get_block_header_by_height", { height: height } );
    let header = MoneroDaemonRpc._buildBlockHeader(resp.block_header);
    MoneroDaemonRpc._setResponseInfo(resp, header);
    return header;
  }
  
  async getBlockHeadersByRange(startHeight, endHeight) {
    await this._initOneTime();
    
    // fetch block headers
    let resp = await this.config.rpc.sendJsonRpcRequest("get_block_headers_range", {
      start_height: startHeight,
      end_height: endHeight
    });
    
    // build headers
    let headers = [];
    for (let respHeader of resp.headers) {
      let header = MoneroDaemonRpc._buildBlockHeader(respHeader);
      headers.push(header);
      MoneroDaemonRpc._setResponseInfo(resp, header);
    }
    return headers;
  }
  
  async getBlockByHash(hash) {
    await this._initOneTime();
    let resp = await this.config.rpc.sendJsonRpcRequest("get_block", { hash: hash });
    let block = MoneroDaemonRpc._buildBlock(resp);
    MoneroDaemonRpc._setResponseInfo(resp, block);
    return block;
  }
  
  async getBlockByHeight(height) {
    await this._initOneTime();
    let resp = await this.config.rpc.sendJsonRpcRequest("get_block", { height: height });
    let block = MoneroDaemonRpc._buildBlock(resp);
    MoneroDaemonRpc._setResponseInfo(resp, block);
    return block;
  }
  
  async getBlocksByHeight(heights) {
    await this._initOneTime();
    
    // fetch blocks in binary
    let respBin = await this.config.rpc.sendBinRpcRequest("get_blocks_by_height.bin", { heights: heights });
    
    // convert binary blocks to json
    let rpcBlocks = this.coreUtils.binary_blocks_to_json(respBin);
    
    // build complete blocks
    assert.equal(rpcBlocks.blocks.length, rpcBlocks.txs.length);    
    let blocks = [];
    for (let blockIdx = 0; blockIdx < rpcBlocks.blocks.length; blockIdx++) {
      let block = MoneroDaemonRpc._buildBlock(rpcBlocks.blocks[blockIdx]);                  // create block
      block.getHeader().setHeight(heights[blockIdx]);                                       // set header height
      block.setTxs(rpcBlocks.txs[blockIdx].map(rpcTx => MoneroDaemonRpc._buildTx(rpcTx)));  // create transactions
      for (let txIdx = 0; txIdx < block.getTxs().length; txIdx++) {
        block.getTxs()[txIdx].setId(rpcBlocks.blocks[blockIdx].tx_hashes[txIdx]);           // set tx id
        block.getTxs()[txIdx].setHeight(block.getHeader().getHeight());                     // set tx height
      }
      MoneroDaemonRpc._setResponseInfo(rpcBlocks, block);
      blocks.push(block);
    }
    
    return blocks;
  }
  
  async getBlocksByRange(startHeight, endHeight) {
    await this._initOneTime();
    if (typeof startHeight !== "number") startHeight = 0;
    if (typeof endHeight !== "number") endHeight = await this.getHeight() - 1;
    let heights = [];
    for (let height = startHeight; height <= endHeight; height++) heights.push(height);
    return await this.getBlocksByHeight(heights);
  }
  
  async getTxs(txHashes, decodeAsJson, prune) {
    await this._initOneTime();
    
    // fetch transactions
    let resp = await this.config.rpc.sendPathRpcRequest("get_transactions", {
      txs_hashes: txHashes,
      decode_as_json: decodeAsJson,
      prune: prune
    });
    
    // build transaction models
    let txs = resp.txs ? resp.txs.map(tx => MoneroDaemonRpc._buildTx(tx)) : [];
    txs.map(tx => MoneroDaemonRpc._setResponseInfo(resp, tx));
    return txs;
  }
  
  async getInfo() {
    await this._initOneTime();
    let resp = await this.config.rpc.sendJsonRpcRequest("get_info");
    let info = MoneroDaemonRpc._buildInfo(resp);
    MoneroDaemonRpc._setResponseInfo(resp, info);
    return info;
  }
  
  async getSyncInfo() {
    await this._initOneTime();
    throw new Error("Not implemented");
  }
  
  async getConnections() {
    await this._initOneTime();
    throw new Error("Not implemented");
  }
  
  // ------------------------------- PRIVATE STATIC ---------------------------
  
  async _initOneTime() {
    
    // return singleton promise if already initialized
    if (this.initPromise) return this.initPromise;
    
    // get core utils
    this.coreUtils = await MoneroUtils.getCoreUtils();
  }
  
  static _setResponseInfo(resp, model) {
    let responseInfo = new MoneroDaemonResponseInfo(resp.status, resp.untrusted ? !resp.untrusted : resp.untrusted);  // invert api's isUntrusted to isTrusted  // TODO: uninvert
    model.setResponseInfo(responseInfo);
  }
  
  static _buildBlockHeader(rpcHeader) {
    if (!rpcHeader) return undefined;
    let header = new MoneroBlockHeader();
    for (var prop in rpcHeader) {
      let key = prop.toString();
      let val = rpcHeader[key];
      if (key === "block_size") header.setBlockSize(val);
      else if (key === "depth") header.setDepth(val);
      else if (key === "difficulty") header.setDifficulty(new BigInteger(val));
      else if (key === "cumulative_difficulty") header.setCumulativeDifficulty(new BigInteger(val));
      else if (key === "hash") header.setHash(val);
      else if (key === "height") header.setHeight(val);
      else if (key === "major_version") header.setMajorVersion(val);
      else if (key === "minor_version") header.setMinorVersion(val);
      else if (key === "nonce") header.setNonce(val);
      else if (key === "num_txes") header.setNumTxs(val);
      else if (key === "orphan_status") header.setOrphanStatus(val);
      else if (key === "prev_hash" || key === "prev_id") header.setPrevHash(val);
      else if (key === "reward") header.setReward(new BigInteger(val));
      else if (key === "timestamp") header.setTimestamp(val);
      else if (key === "block_weight") header.setBlockWeight(val);
      else if (key === "pow_hash") header.setPowHash(val === "" ? undefined : val);
      //else console.log("WARNING: ignoring unexpected block header field: '" + key + "': " + val); // TODO: if ignoring warning, use safe set like below
    }
    return header;
  }
  
  static _buildBlock(rpcBlock) {
    let block = new MoneroBlock();
    block.setHex(rpcBlock.blob);
    block.setHeader(MoneroDaemonRpc._buildBlockHeader(rpcBlock.block_header ? rpcBlock.block_header : rpcBlock));
    block.setTxHashes(rpcBlock.tx_hashes === undefined ? [] : rpcBlock.tx_hashes);
    let minerTxRpc = rpcBlock.json ? JSON.parse(rpcBlock.json).miner_tx : rpcBlock.miner_tx; // get miner tx from rpc
    block.setMinerTx(MoneroDaemonRpc._buildTx(minerTxRpc));
    return block;
  }
  
  /**
   * Transfers RPC tx fields to a given MoneroTx without overwriting previous values.
   * 
   * @param rpcTx is the RPC map containing transaction fields
   * @param tx is the MoneroTx to populate with values (optional)
   * @returns tx is the same tx that was passed in or a new one if none given
   */
  static _buildTx(rpcTx, tx) {
    if (!tx) tx = new MoneroTx();
    if (rpcTx === undefined) return tx;
    MoneroUtils.safeSet(tx, tx.getHex, tx.setHex, rpcTx.as_hex);
    MoneroUtils.safeSet(tx, tx.getHeight, tx.setHeight, rpcTx.block_height);
    MoneroUtils.safeSet(tx, tx.getTimestamp, tx.setTimestamp, rpcTx.block_timestamp);
    MoneroUtils.safeSet(tx, tx.getIsDoubleSpend, tx.setIsDoubleSpend, rpcTx.double_spend_seen);
    MoneroUtils.safeSet(tx, tx.getIsConfirmed, tx.setIsConfirmed, rpcTx.in_pool === undefined ? undefined : !rpcTx.in_pool);
    MoneroUtils.safeSet(tx, tx.getId, tx.setId, rpcTx.tx_hash);
    MoneroUtils.safeSet(tx, tx.getVersion, tx.setVersion, rpcTx.version);
    MoneroUtils.safeSet(tx, tx.getExtra, tx.setExtra, rpcTx.extra);
    MoneroUtils.safeSet(tx, tx.getVin, tx.setVin, rpcTx.vin);
    MoneroUtils.safeSet(tx, tx.getVout, tx.setVout, rpcTx.vout);
    MoneroUtils.safeSet(tx, tx.getRctSignatures, tx.setRctSignatures, rpcTx.rct_signatures);
    MoneroUtils.safeSet(tx, tx.getRctSigPrunable, tx.setRctSigPrunable, rpcTx.rctsig_prunable);
    MoneroUtils.safeSet(tx, tx.getUnlockTime, tx.setUnlockTime, rpcTx.unlock_time);
    if (rpcTx.as_json) MoneroDaemonRpc._buildTx(JSON.parse(rpcTx.as_json), tx);  // may need to read tx from json str
    return tx;
  }
  
  static _buildBlockTemplate(rpcTemplate) {
    let template = new MoneroBlockTemplate();
    for (let key in rpcTemplate) {
      if (!rpcTemplate.hasOwnProperty(key)) continue;
      let val = rpcTemplate[key];
      if (key === "blockhashing_blob") template.setTemplateBlob(val);
      else if (key === "blocktemplate_blob") template.setHashBlob(val);
      else if (key === "difficulty") template.setDifficulty(val);
      else if (key === "expected_reward") template.setExpectedReward(val);
      else if (key === "height") template.setHeight(val);
      else if (key === "prev_hash") template.setPrevHash(val);
      else if (key === "reserved_offset") template.setReservedOffset(val);
      else if (key === "status") {}  // set elsewhere
      else if (key === "untrusted") {}  // set elsewhere
      else console.log("Ignoring unexpected field in block template: '" + key + "'");
    }
    return template;
  }
  
  static _buildInfo(rpcInfo) {
    if (!rpcInfo) return undefined;
    let info = new MoneroDaemonInfo();
    for (var prop in rpcInfo) {
      let key = prop.toString();
      let val = rpcInfo[key];
      if (key === "alt_blocks_count") info.setAltBlocksCount(val);
      else if (key === "block_size_limit") info.setBlockSizeLimit(val);
      else if (key === "block_size_median") info.setBlockSizeMedian(val);
      else if (key === "block_weight_limit") info.setBlockWeightLimit(val);
      else if (key === "block_weight_median") info.setBlockWeightMedian(val);
      else if (key === "bootstrap_daemon_address") info.setBootstrapDaemonAddress(val);
      else if (key === "cumulative_difficulty") info.setCumulativeDifficulty(new BigInteger(val));
      else if (key === "difficulty") info.setDifficulty(new BigInteger(val));
      else if (key === "free_space") info.setFreeSpace(new BigInteger(val));
      else if (key === "database_size") info.setDatabaseSize(new BigInteger(val));  // TODO: big integers necessary?  test?
      else if (key === "grey_peerlist_size") info.setGreyPeerlistSize(val);
      else if (key === "height") info.setHeight(val);
      else if (key === "height_without_bootstrap") info.setHeightWithoutBootstrap(val);
      else if (key === "incoming_connections_count") info.setIncomingConnectionsCount(val);
      else if (key === "offline") info.setIsOffline(val);
      else if (key === "outgoing_connections_count") info.setOutgoingConnectionsCount(val);
      else if (key === "rpc_connections_count") info.setRpcConnectionsCount(val);
      else if (key === "start_time") info.setStartTime(val);
      else if (key === "status") {}  // set elsewhere
      else if (key === "target") info.setTarget(val);
      else if (key === "target_height") info.setTargetHeight(val);
      else if (key === "top_block_hash") info.setTopBlockHash(val);
      else if (key === "tx_count") info.setTxCount(val);
      else if (key === "tx_pool_size") info.setTxPoolSize(val);
      else if (key === "untrusted") {} // set elsewhere
      else if (key === "was_bootstrap_ever_used") info.setWasBootstrapEverUsed(val);
      else if (key === "white_peerlist_size") info.setWhitePeerlistSize(val);
      else if (key === "update_available") info.setUpdateAvailable(val);
      else if (key === "nettype") MoneroUtils.safeSet(info, info.getNetworkType, info.setNetworkType, MoneroDaemon.parseNetworkType(val));
      else if (key === "mainnet") { if (val) MoneroUtils.safeSet(info, info.getNetworkType, info.setNetworkType, MoneroDaemon.NetworkType.MAINNET); }
      else if (key === "testnet") { if (val) MoneroUtils.safeSet(info, info.getNetworkType, info.setNetworkType, MoneroDaemon.NetworkType.TESTNET); }
      else if (key === "stagenet") { if (val) MoneroUtils.safeSet(info, info.getNetworkType, info.setNetworkType, MoneroDaemon.NetworkType.STAGENET); }
      else console.log("WARNING: Ignoring unexpected info field: " + key + ": " + val);
    }
    return info;
  }
}

module.exports = MoneroDaemonRpc;