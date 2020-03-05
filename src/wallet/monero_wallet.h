/**
 * Copyright (c) 2017-2019 woodser
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Parts of this file are originally copyright (c) 2014-2019, The Monero Project
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 * All rights reserved.
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers
 */

#pragma once

#include "monero_wallet_model.h"

using namespace std;
using namespace monero;

/**
 * Public library interface.
 */
namespace monero {

  // --------------------------------- LISTENERS ------------------------------

  /**
   * Receives progress notifications as a wallet is synchronized.
   *
   * TODO: make these interfaces and provide default implementation
   */
  class monero_sync_listener {
  public:

    /**
     * Invoked when sync progress is made.
     *
     * @param height is the height of the synced block
     * @param start_height is the starting height of the sync request
     * @param end_height is the ending height of the sync request
     * @param percent_done is the sync progress as a percentage
     * @param message is a human-readable description of the current progress
     */
    virtual void on_sync_progress(uint64_t height, uint64_t start_height, uint64_t end_height, double percent_done, const string& message) {}
  };

  /**
   * Receives notifications as a wallet is updated.
   */
  class monero_wallet_listener : public monero_sync_listener {
  public:

    /**
     * Invoked when a new block is processed.
     *
     * @param block is the newly processed block
     */
    virtual void on_new_block(uint64_t height) {};

    /**
     * Invoked when the wallet receives an output.
     *
     * @param output is the incoming output to the wallet
     */
    virtual void on_output_received(const monero_output_wallet& output) {};

    /**
     * Invoked when the wallet spends an output.
     *
     * @param output the outgoing transfer from the wallet
     */
    virtual void on_output_spent(const monero_output_wallet& output) {};
  };

  // forward declaration of internal wallet2 listener
  struct wallet2_listener;

  // ----------------------------- WALLET METHODS -----------------------------

  /**
   * Base wallet with default implementations.
   */
  class monero_wallet {

  public:

    /**
     * Virtual destructor.
     */
    virtual ~monero_wallet() {}

    /**
     * Set the wallet's daemon connection.
     *
     * @param uri is the daemon's URI
     * @param username is the username to authenticate with the daemon (optional)
     * @param password is the password to authenticate with the daemon (optional)
     */
    virtual void set_daemon_connection(const string& uri, const string& username = "", const string& password = "") {
      throw runtime_error("set_daemon_connection() not supported");
    }

    /**
     * Set the wallet's daemon connection.
     *
     * @param connection is the connection to set
     */
    virtual void set_daemon_connection(const boost::optional<monero_rpc_connection>& connection) {
      throw runtime_error("set_daemon_connection() not supported");
    }

    /**
     * Get the wallet's daemon connection.
     *
     * @return the wallet's daemon connection
     */
    virtual boost::optional<monero_rpc_connection> get_daemon_connection() const {
      throw runtime_error("get_daemon_connection() not supported");
    }

    /**
     * Indicates if the wallet is connected a daemon.
     *
     * @return true if the wallet is connected to a daemon, false otherwise
     */
    virtual bool is_connected() const {
      throw runtime_error("is_connected() not supported");
    }

    /**
     * Indicates if the wallet's daemon is synced with the network.
     *
     * @return true if the daemon is synced with the network, false otherwise
     */
    virtual bool is_daemon_synced() const {
      throw runtime_error("is_daemon_synced() not supported");
    }

    /**
     * Indicates if the daemon is trusted or untrusted.
     *
     * @return true if the daemon is trusted, false otherwise
     */
    virtual bool is_daemon_trusted() const {
      throw runtime_error("is_daemon_trusted() not supported");
    }

    /**
     * Indicates if the wallet is synced with the daemon.
     *
     * @return true if the wallet is synced with the daemon, false otherwise
     */
    virtual bool is_synced() const {
      throw runtime_error("is_synced() not supported");
    }

    /**
     * Get the wallet's version.
     *
     * @return the wallet's version
     */
    virtual monero_version get_version() const {
      throw runtime_error("get_version() not supported");
    }

    /**
     * Get the path of this wallet's file on disk.
     *
     * @return the path of this wallet's file on disk
     */
    virtual string get_path() const {
      throw runtime_error("get_path() not supported");
    }

    /**
     * Get the wallet's network type (mainnet, testnet, or stagenet).
     *
     * @return the wallet's network type
     */
    virtual monero_network_type get_network_type() const {
      throw runtime_error("get_network_type() not supported");
    }

    /**
     * Get the wallet's mnemonic phrase.
     *
     * @param mnemonic is assigned the wallet's mnemonic phrase
     */
    virtual string get_mnemonic() const {
      throw runtime_error("get_mnemonic() not supported");
    }

    /**
     * Get the language of the wallet's mnemonic phrase.
     *
     * @return the language of the wallet's mnemonic phrase
     */
    virtual string get_mnemonic_language() const {
      throw runtime_error("get_mnemonic_language() not supported");
    }

    /**
     * Get the wallet's public view key.
     *
     * @return the wallet's public view key
     */
    virtual string get_public_view_key() const {
      throw runtime_error("get_public_view_key() not supported");
    }

    /**
     * Get the wallet's private view key.
     *
     * @return the wallet's private view key
     */
    virtual string get_private_view_key() const {
      throw runtime_error("get_private_view_key() not supported");
    }

    /**
     * Get the wallet's public spend key.
     *
     * @return the wallet's public spend key
     */
    virtual string get_public_spend_key() const {
      throw runtime_error("get_public_spend_key() not supported");
    }

    /**
     * Get the wallet's private spend key.
     *
     * @return the wallet's private spend key
     */
    virtual string get_private_spend_key() const {
      throw runtime_error("get_private_spend_key() not supported");
    }

    /**
     * Get the wallet's primary address.
     *
     * @return the wallet's primary address
     */
    virtual string get_primary_address() const {
      return get_address(0, 0);
    }

    /**
     * Get the address of a specific subaddress.
     *
     * @param account_idx specifies the account index of the address's subaddress
     * @param subaddress_idx specifies the subaddress index within the account
     * @return the receive address of the specified subaddress
     */
    virtual string get_address(const uint32_t account_idx, const uint32_t subaddress_idx) const {
      throw runtime_error("get_address() not supported");
    }

    /**
     * Get the account and subaddress index of the given address.
     *
     * @param address is the address to get the account and subaddress index from
     * @return the account and subaddress indices
     * @throws exception if address is not a wallet address
     */
    virtual monero_subaddress get_address_index(const string& address) const {
      throw runtime_error("get_address_index() not supported");
    }

    /**
     * Get an integrated address from a standard address and a payment id.
     *
     * @param standard_address is the integrated addresse's standard address (defaults to wallet's primary address)
     * @param payment_id is the integrated addresse's payment id (defaults to randomly generating new payment id)
     * @return the integrated address
     */
    virtual monero_integrated_address get_integrated_address(const string& standard_address = "", const string& payment_id = "") const {
      throw runtime_error("get_integrated_address() not supported");
    }

    /**
     * Decode an integrated address to get its standard address and payment id.
     *
     * @param integrated_address is an integrated address to decode
     * @return the decoded integrated address including standard address and payment id
     */
    virtual monero_integrated_address decode_integrated_address(const string& integrated_address) const {
      throw runtime_error("decode_integrated_address() not supported");
    }

    /**
     * Get the height of the last block processed by the wallet (its index + 1).
     *
     * @return the height of the last block processed by the wallet
     */
    virtual uint64_t get_height() const {
      throw runtime_error("get_height() not supported");
    }

    /**
     * Get the height of the first block that the wallet scans.
     *
     * @return the height of the first block that the wallet scans
     */
    virtual uint64_t get_restore_height() const {
      throw runtime_error("get_restore_height() not supported");
    }

    /**
     * Set the height of the first block that the wallet scans.
     *
     * @param restore_height is the height of the first block that the wallet scans
     */
    virtual void set_restore_height(uint64_t restore_height) {
      throw runtime_error("set_restore_height() not supported");
    }

    /**
     * Get the height that the wallet's daemon is synced to.
     *
     * @return the height that the wallet's daemon is synced to
     */
    virtual uint64_t get_daemon_height() const {
      throw runtime_error("get_daemon_height() not supported");
    }

    /**
     * Get the maximum height of the peers the wallet's daemon is connected to.
     *
     * @return the maximum height of the peers the wallet's daemon is connected to
     */
    virtual uint64_t get_daemon_max_peer_height() const {
      throw runtime_error("get_daemon_max_peer_height() not supported");
    }

    /**
     * Register a listener receive wallet notifications.
     *
     * @param listener is the listener to receive wallet notifications
     */
    virtual void add_listener(monero_wallet_listener& listener) {
      throw runtime_error("add_listener() not supported");
    }

    /**
     * Unregister a listener to receive wallet notifications.
     *
     * @param listener is the listener to unregister
     */
    virtual void remove_listener(monero_wallet_listener& listener) {
      throw runtime_error("remove_listener() not supported");
    }

    /**
     * Get the listeners registered with the wallet.
     */
    virtual set<monero_wallet_listener*> get_listeners() {
      throw runtime_error("get_listeners() not supported");
    }

    /**
     * Synchronize the wallet with the daemon as a one-time synchronous process.
     *
     * @return the sync result
     */
    virtual monero_sync_result sync() {
      throw runtime_error("sync() not supported");
    }

    /**
     * Synchronize the wallet with the daemon as a one-time synchronous process.
     *
     * @param listener is invoked as sync progress is made
     * @return the sync result
     */
    virtual monero_sync_result sync(monero_sync_listener& listener) {
      throw runtime_error("sync() not supported");
    }

    /**
     * Synchronize the wallet with the daemon as a one-time synchronous process.
     *
     * @param start_height is the start height to sync from (ignored if less than last processed block)
     * @return the sync result
     */
    virtual monero_sync_result sync(uint64_t start_height) {
      throw runtime_error("sync() not supported");
    }

    /**
     * Synchronizes the wallet with the blockchain.
     *
     * @param start_height is the start height to sync from (ignored if less than last processed block)
     * @param listener is invoked as sync progress is made
     * @return the sync result
     */
    virtual monero_sync_result sync(uint64_t start_height, monero_sync_listener& listener) {
      throw runtime_error("sync() not supported");
    }

    /**
     * Start an asynchronous thread to continuously synchronize the wallet with the daemon.
     */
    virtual void start_syncing() {
      throw runtime_error("start_syncing() not supported");
    }

    /**
     * Stop the asynchronous thread to continuously synchronize the wallet with the daemon.
     */
    virtual void stop_syncing() {
      throw runtime_error("stop_syncing() not supported");
    }

    /**
     * Rescan the blockchain for spent outputs.
     *
     * Note: this can only be called with a trusted daemon.
     *
     * Example use case: peer multisig hex is import when connected to an untrusted daemon,
     * so the wallet will not rescan spent outputs.  Then the wallet connects to a trusted
     * daemon.  This method should be manually invoked to rescan outputs.
     */
    virtual void rescan_spent() {
      throw runtime_error("rescan_spent() not supported");
    }

    /**
     * Rescan the blockchain from scratch, losing any information which cannot be recovered from
     * the blockchain itself.
     *
     * WARNING: This method discards local wallet data like destination addresses, tx secret keys,
     * tx notes, etc.
     */
    virtual void rescan_blockchain() {
      throw runtime_error("rescan_blockchain() not supported");
    }

//    /**
//     * Indicates if importing multisig data is needed for returning a correct balance.
//     *
//     * @return true if importing multisig data is needed for returning a correct balance, false otherwise
//     */
//    public boolean isMultisigImportNeeded();

    /**
     * Get the wallet's balance.
     *
     * @return the wallet's balance
     */
    virtual uint64_t get_balance() const {
      throw runtime_error("get_balance() not supported");
    }

    /**
     * Get an account's balance.
     *
     * @param account_idx is the index of the account to get the balance of
     * @return the account's balance
     */
    virtual uint64_t get_balance(uint32_t account_idx) const {
      throw runtime_error("get_balance() not supported");
    }

    /**
     * Get a subaddress's balance.
     *
     * @param account_idx is the index of the subaddress's account to get the balance of
     * @param subaddress_idx is the index of the subaddress to get the balance of
     * @return the subaddress's balance
     */
    virtual uint64_t get_balance(uint32_t account_idx, uint32_t subaddress_idx) const {
      throw runtime_error("get_balance() not supported");
    }

    /**
     * Get the wallet's unlocked balance.
     *
     * @return the wallet's unlocked balance
     */
    virtual uint64_t get_unlocked_balance() const {
      throw runtime_error("get_unlocked_balance() not supported");
    }

    /**
     * Get an account's unlocked balance.
     *
     * @param account_idx is the index of the account to get the unlocked balance of
     * @return the account's unlocked balance
     */
    virtual uint64_t get_unlocked_balance(uint32_t account_idx) const {
      throw runtime_error("get_unlocked_balance() not supported");
    }

    /**
     * Get a subaddress's unlocked balance.
     *
     * @param account_idx is the index of the subaddress's account to get the unlocked balance of
     * @param subaddress_idx is the index of the subaddress to get the unlocked balance of
     * @return the subaddress's balance
     */
    virtual uint64_t get_unlocked_balance(uint32_t account_idx, uint32_t subaddress_idx) const {
      throw runtime_error("get_unlocked_balance() not supported");
    }

    /**
     * Get all accounts.
     *
     * @return List<monero_account> are all accounts within the wallet
     */
    virtual vector<monero_account> get_accounts() const {
      return get_accounts(false, string(""));
    }

    /**
     * Get all accounts.
     *
     * @param include_subaddresses specifies if subaddresses should be included
     * @return List<monero_account> are all accounts
     */
    virtual vector<monero_account> get_accounts(bool include_subaddresses) const {
      return get_accounts(include_subaddresses, "");
    }

    /**
     * Get accounts with a given tag.
     *
     * @param tag is the tag for filtering accounts, all accounts if null
     * @return List<monero_account> are all accounts for the wallet with the given tag
     */
    virtual vector<monero_account> get_accounts(const string& tag) const {
      return get_accounts(false, tag);
    }

    /**
     * Get accounts with a given tag.
     *
     * @param include_subaddresses specifies if subaddresses should be included
     * @param tag is the tag for filtering accounts, all accounts if null
     * @return List<monero_account> are all accounts for the wallet with the given tag
     */
    virtual vector<monero_account> get_accounts(bool include_subaddresses, const string& tag) const {
      throw runtime_error("get_accounts() not supported");
    }

    /**
     * Get an account without subaddress information.
     *
     * @param account_idx specifies the account to get
     * @return the retrieved account
     */
    virtual monero_account get_account(uint32_t account_idx) const {
      return get_account(account_idx, false);
    }

    /**
     * Get an account.
     *
     * @param account_idx specifies the account to get
     * @param include_subaddresses specifies if subaddresses should be included
     * @return the retrieved account
     */
    virtual monero_account get_account(const uint32_t account_idx, bool include_subaddresses) const {
      throw runtime_error("get_account() not supported");
    }

    /**
     * Create a new account with a label for the first subaddress.
     *
     * @param label specifies the label for the account's first subaddress (optional)
     * @return the created account
     */
    virtual monero_account create_account(const string& label = "") {
      throw runtime_error("create_account() not supported");
    }

    /**
     * Get all subaddresses in an account.
     *
     * @param account_idx specifies the account to get subaddresses within
     * @return List<monero_subaddress> are the retrieved subaddresses
     */
    virtual vector<monero_subaddress> get_subaddresses(const uint32_t account_idx) const {
      return get_subaddresses(account_idx, vector<uint32_t>());
    }

    /**
     * Get subaddresses in an account.
     *
     * @param account_idx specifies the account to get subaddresses within
     * @param subaddress_indices are specific subaddresses to get (optional)
     * @return the retrieved subaddresses
     */
    virtual vector<monero_subaddress> get_subaddresses(const uint32_t account_idx, const vector<uint32_t>& subaddress_indices) const {
      throw runtime_error("get_subaddresses() not supported");
    }

    /**
     * Get a subaddress.
     *
     * @param account_idx specifies the index of the subaddress's account
     * @param subaddress_idx specifies index of the subaddress within the account
     * @return the retrieved subaddress
     */
    virtual monero_subaddress get_subaddress(const uint32_t account_idx, const uint32_t subaddress_idx) const {
      throw runtime_error("get_subaddress() not supported");
    }

    /**
     * Create a subaddress within an account.
     *
     * @param account_idx specifies the index of the account to create the subaddress within
     * @param label specifies the the label for the subaddress (defaults to empty string)
     * @return the created subaddress
     */
    virtual monero_subaddress create_subaddress(uint32_t account_idx, const string& label = "") {
      throw runtime_error("create_subaddress() not supported");
    }

//    /**
//     * Get a wallet transaction by hash.
//     *
//     * @param tx_hash is a hash of a transaction to get
//     * @return monero_tx_wallet is the identified transactions
//     */
//    public monero_tx_wallet getTx(string tx_hash);

    /**
     * Get all wallet transactions.  Wallet transactions contain one or more
     * transfers that are either incoming or outgoing to the wallet.
     *
     * @return all wallet transactions
     */
    virtual vector<shared_ptr<monero_tx_wallet>> get_txs() const {
      throw runtime_error("get_txs() not supported");
    }

//    /**
//     * Get wallet transactions by hash.
//     *
//     * @param tx_hashes are hashes of transactions to get
//     * @return the identified transactions
//     */
//    public List<monero_tx_wallet> get_txs(Collection<string> tx_hashes);

    /**
     * Get wallet transactions.  Wallet transactions contain one or more
     * transfers that are either incoming or outgoing to the wallet.
     *
     * Query results can be filtered by passing in a transaction query.
     * Transactions must meet every criteria defined in the query in order to
     * be returned.  All filtering is optional and no filtering is applied when
     * not defined.
     *
     * @param query filters query results (optional)
     * @return wallet transactions per the query
     */
    virtual vector<shared_ptr<monero_tx_wallet>> get_txs(const monero_tx_query& query) const {
      throw runtime_error("get_txs(query) not supported");
    }

    /**
     * Same as get_txs(request) but collects missing tx hashes instead of throwing an error.
     * This method is separated because WebAssembly does not support exception handling.
     *
     * @param request filters query results (optional)
     * @param missing_tx_hashes are populated with requested tx hashes that are not part of the wallet
     * @return wallet transactions per the request
     */
    virtual vector<shared_ptr<monero_tx_wallet>> get_txs(const monero_tx_query& query, vector<string>& missing_tx_hashes) const {
      throw runtime_error("get_txs(query, missing_tx_hashes) not supported");
    }

//    /**
//     * Get all incoming and outgoing transfers to and from this wallet.  An
//     * outgoing transfer represents a total amount sent from one or more
//     * subaddresses within an account to individual destination addresses, each
//     * with their own amount.  An incoming transfer represents a total amount
//     * received into a subaddress within an account.  Transfers belong to
//     * transactions which are stored on the blockchain.
//     *
//     * @return all wallet transfers
//     */
//    public List<monero_transfer> get_transfers();
//
//    /**
//     * Get incoming and outgoing transfers to and from an account.  An outgoing
//     * transfer represents a total amount sent from one or more subaddresses
//     * within an account to individual destination addresses, each with their
//     * own amount.  An incoming transfer represents a total amount received into
//     * a subaddress within an account.  Transfers belong to transactions which
//     * are stored on the blockchain.
//     *
//     * @param account_idx is the index of the account to get transfers from
//     * @return transfers to/from the account
//     */
//    public List<monero_transfer> get_transfers(int account_idx);
//
//    /**
//     * Get incoming and outgoing transfers to and from a subaddress.  An outgoing
//     * transfer represents a total amount sent from one or more subaddresses
//     * within an account to individual destination addresses, each with their
//     * own amount.  An incoming transfer represents a total amount received into
//     * a subaddress within an account.  Transfers belong to transactions which
//     * are stored on the blockchain.
//     *
//     * @param account_idx is the index of the account to get transfers from
//     * @param subaddress_idx is the index of the subaddress to get transfers from
//     * @return transfers to/from the subaddress
//     */
//    public List<monero_transfer> get_transfers(int account_idx, int subaddress_idx);

    /**
     * Get incoming and outgoing transfers to and from this wallet.  An outgoing
     * transfer represents a total amount sent from one or more subaddresses
     * within an account to individual destination addresses, each with their
     * own amount.  An incoming transfer represents a total amount received into
     * a subaddress within an account.  Transfers belong to transactions which
     * are stored on the blockchain.
     *
     * Query results can be filtered by passing in a monero_transfer_query.
     * Transfers must meet every criteria defined in the query in order to be
     * returned.  All filtering is optional and no filtering is applied when not
     * defined.
     *
     * @param query filters query results (optional)
     * @return wallet transfers per the query
     */
    virtual vector<shared_ptr<monero_transfer>> get_transfers(const monero_transfer_query& query) const {
      throw runtime_error("get_transfers() not supported");
    }

//    /**
//     * Get outputs created from previous transactions that belong to the wallet
//     * (i.e. that the wallet can spend one time).  Outputs are part of
//     * transactions which are stored in blocks on the blockchain.
//     *
//     * @return List<monero_output_wallet> are all wallet outputs
//     */
//    public List<monero_output_wallet> get_outputs();

    /**
     * Get outputs created from previous transactions that belong to the wallet
     * (i.e. that the wallet can spend one time).  Outputs are part of
     * transactions which are stored in blocks on the blockchain.
     *
     * Results can be configured by passing a monero_output_query.  Outputs must
     * meet every criteria defined in the query in order to be returned.  All
     * filtering is optional and no filtering is applied when not defined.
     *
     * @param query specifies query options (optional)
     * @return wallet outputs per the query
     */
    virtual vector<shared_ptr<monero_output_wallet>> get_outputs(const monero_output_query& query) const {
      throw runtime_error("get_outputs() not supported");
    }

    /**
     * Export all outputs in hex format.
     *
     * @return all outputs in hex format, empty string if no outputs
     */
    virtual string get_outputs_hex() const {
      throw runtime_error("get_outputs_hex() not supported");
    }

    /**
     * Import outputs in hex format.
     *
     * @param outputs_hex are outputs in hex format
     * @return the number of outputs imported
     */
    virtual int import_outputs_hex(const string& outputs_hex) {
      throw runtime_error("import_outputs_hex() not supported");
    }

    /**
     * Get all signed key images.
     *
     * @return the wallet's signed key images
     */
    virtual vector<shared_ptr<monero_key_image>> get_key_images() const {
      throw runtime_error("get_key_images() not supported");
    }

    /**
     * Import signed key images and verify their spent status.
     *
     * @param key_images are key images to import and verify (requires hex and signature)
     * @return results of the import
     */
    virtual shared_ptr<monero_key_image_import_result> import_key_images(const vector<shared_ptr<monero_key_image>>& key_images) {
      throw runtime_error("import_key_images() not supported");
    }

//    /**
//     * Get new key images from the last imported outputs.
//     *
//     * @return the key images from the last imported outputs
//     */
//    public List<monero_key_image> getNewKeyImagesFromLastImport();

    /**
     * Create a transaction to transfer funds from this wallet according to the
     * given request.  The transaction may be relayed later.
     *
     * @param request configures the transaction to create
     * @return a tx set for the requested transaction if possible
     */
    virtual monero_tx_set create_tx(monero_send_request& request) {
      throw runtime_error("create_tx() not supported");
    }

    /**
     * Create a transaction to transfers funds from this wallet to a destination address.
     * The transaction may be relayed later.
     *
     * @param accountIndex is the index of the account to withdraw funds from
     * @param address is the destination address to send funds to
     * @param amount is the amount being sent
     * @return a tx set for the requested transaction if possible
     */
    virtual monero_tx_set create_tx(uint32_t account_index, string address, uint64_t amount) {
      throw runtime_error("create_tx() not supported");
    }

    /**
     * Create a transaction to transfers funds from this wallet to a destination address.
     * The transaction may be relayed later.
     *
     * @param accountIndex is the index of the account to withdraw funds from
     * @param address is the destination address to send funds to
     * @param amount is the amount being sent
     * @param priority is the send priority (default normal)
     * @return a tx set for the requested transaction if possible
     */
    virtual monero_tx_set create_tx(int account_index, string address, uint64_t amount, monero_send_priority priority) {
      throw runtime_error("create_tx() not supported");
    }

    /**
     * Create one or more transactions to transfer funds from this wallet
     * according to the given request.  The transactions may later be relayed.
     *
     * @param request configures the transactions to create
     * @return a tx set for the requested transactions if possible
     */
    virtual monero_tx_set create_txs(monero_send_request& request) {
      throw runtime_error("create_txs() not supported");
    }

    /**
     * Relay a transaction previously created without relaying.
     *
     * @param txMetadata is transaction metadata previously created without relaying
     * @return string is the hash of the relayed tx
     */
    virtual string relay_tx(const string& tx_metadata) {
      throw runtime_error("relay_tx() not supported");
    }

    /**
     * Relay a previously created transaction.
     *
     * @param tx is the transaction to relay
     * @return the hash of the relayed tx
     */
    virtual string relay_tx(const monero_tx_wallet& tx) {
      throw runtime_error("relay_tx() not supported");
    }

    /**
     * Relay transactions previously created without relaying.
     *
     * @param tx_metadatas are transaction metadata previously created without relaying
     * @return the hashes of the relayed txs
     */
    virtual vector<string> relay_txs(const vector<string>& tx_metadatas) {
      throw runtime_error("relay_txs() not supported");
    }

    /**
     * Relay previously created transactions.
     *
     * @param txs are the transactions to relay
     * @return the hashes of the relayed txs
     */
    virtual vector<string> relay_txs(const vector<shared_ptr<monero_tx_wallet>>& txs) {
      throw runtime_error("relay_txs() not supported");
    }

    /**
     * Create and relay a transaction to transfer funds from this wallet
     * according to the given request.
     *
     * @param request configures the transaction
     * @return a tx set with the requested transaction if possible
     */
    virtual monero_tx_set send(const monero_send_request& request) {
      throw runtime_error("send() not supported");
    }

    /**
     * Create and relay a transaction to transfers funds from this wallet to
     * a destination address.
     *
     * @param account_index is the index of the account to withdraw funds from
     * @param address is the destination address to send funds to
     * @param amount is the amount being sent
     * @return a tx set with the requested transaction if possible
     */
    virtual monero_tx_set send(uint32_t account_index, string address, uint64_t amount) {
      throw runtime_error("send() not supported");
    }

    /**
     * Create and relay a transaction to transfers funds from this wallet to
     * a destination address.
     *
     * @param account_index is the index of the account to withdraw funds from
     * @param address is the destination address to send funds to
     * @param amount is the amount being sent
     * @param priority is the send priority (default normal)
     * @return a tx set with the requested transaction if possible
     */
    virtual monero_tx_set send(uint32_t account_index, string address, uint64_t amount, monero_send_priority priority) {
      throw runtime_error("send() not supported");
    }

    /**
     * Create one or more transactions which transfer funds from this wallet to
     * one or more destinations depending on the given configuration.
     *
     * @param request configures the transaction
     * @return a tx set with the requested transactions if possible
     */
    virtual monero_tx_set send_split(const monero_send_request& request) {
      throw runtime_error("send_split() not supported");
    }

    //    /**
    //     * Create and relay one or more transactions which transfer funds from this
    //     * wallet to one or more destination.
    //     *
    //     * @param account_index is the index of the account to draw funds from
    //     * @param address is the destination address to send funds to
    //     * @param sendAmount is the amount being sent
    //     * @return the resulting transactions
    //     */
    //    public List<monero_tx_wallet> send_split(int account_index, string address, BigInteger sendAmount);
    //
    //    /**
    //     * Create and relay one or more transactions which transfer funds from this
    //     * wallet to one or more destination.
    //     *
    //     * @param account_index is the index of the account to draw funds from
    //     * @param address is the destination address to send funds to
    //     * @param sendAmount is the amount being sent
    //     * @param priority is the send priority (default normal)
    //     * @return the resulting transactions
    //     */
    //    public List<monero_tx_wallet> send_split(int account_index, string address, BigInteger sendAmount, monero_send_priority priority);

    /**
     * Sweep unlocked funds according to the given request.
     *
     * @param request is the sweep configuration
     * @return the tx sets with the requested transactions
     */
    virtual vector<monero_tx_set> sweep_unlocked(const monero_send_request& request) {
      throw runtime_error("sweep_unlocked() not supported");
    }

    /**
     * Sweep an output with a given key image.
     *
     * @param request configures the sweep transaction
     * @return a tx set with the requested transaction if possible
     */
    virtual monero_tx_set sweep_output(const monero_send_request& request) {
      throw runtime_error("sweep_output() not supported");
    }

//    /**
//     * Sweep an output with a given key image.
//     *
//     * @param address is the destination address to send to
//     * @param key_image is the key image hex of the output to sweep
//     * @return the resulting transaction from sweeping an output
//     */
//    public monero_tx_wallet sweep_output(string address, string key_image);
//
//    /**
//     * Sweep an output with a given key image.
//     *
//     * @param address is the destination address to send to
//     * @param key_image is the key image hex of the output to sweep
//     * @param priority is the transaction priority (optional)
//     * @return the resulting transaction from sweeping an output
//     */
//    public monero_tx_wallet sweep_output(string address, string key_image, monero_send_priority priority);
//
//    /**
//     * Sweep a subaddress's unlocked funds to an address.
//     *
//     * @param account_idx is the index of the account
//     * @param subaddress_idx is the index of the subaddress
//     * @param address is the address to sweep the subaddress's funds to
//     * @return the resulting transactions
//     */
//    public List<monero_tx_wallet> sweepSubaddress(int account_idx, int subaddress_idx, string address);
//
//    /**
//     * Sweep an acount's unlocked funds to an address.
//     *
//     * @param account_idx is the index of the account
//     * @param address is the address to sweep the account's funds to
//     * @return the resulting transactions
//     */
//    public List<monero_tx_wallet> sweepAccount(int account_idx, string address);
//
//    /**
//     * Sweep the wallet's unlocked funds to an address.
//     *
//     * @param address is the address to sweep the wallet's funds to
//     * @return the resulting transactions
//     */
//    public List<monero_tx_wallet> sweepWallet(string address);
//
//    /**
//     * Sweep all unlocked funds according to the given request.
//     *
//     * @param request is the sweep configuration
//     * @return the resulting transactions
//     */
//    public List<monero_tx_wallet> sweepAllUnlocked(monero_send_request request);
//
//    /**
//     * Sweep all unmixable dust outputs back to the wallet to make them easier to spend and mix.
//     *
//     * NOTE: Dust only exists pre RCT, so this method will return "no dust to sweep" on new wallets.
//     *
//     * @return the resulting transactions from sweeping dust
//     */
//    public List<monero_tx_wallet> sweep_dust();

    /**
     * Sweep all unmixable dust outputs back to the wallet to make them easier to spend and mix.
     *
     * @param do_not_relay specifies if the resulting transaction should not be relayed (defaults to false i.e. relayed)
     * @return a tx set with the requested transactions if possible
     */
    virtual monero_tx_set sweep_dust(bool do_not_relay = false) {
      throw runtime_error("sweep_dust() not supported");
    }

    /**
     * Parses a tx set containing unsigned or multisig tx hex to a new tx set containing structured transactions.
     *
     * @param tx_set is a tx set containing unsigned or multisig tx hex
     * @return the parsed tx set containing structured transactions
     */
    virtual monero_tx_set parse_tx_set(const monero_tx_set& tx_set) {
      throw runtime_error("parse_tx_set() not supported");
    }

    /**
     * Sign unsigned transactions from a watch-only wallet.
     *
     * @param unsigned_tx_hex is unsigned transaction hex from when the transactions were created
     * @return the signed transaction hex
     */
    virtual string sign_txs(const string& unsigned_tx_hex) {
      throw runtime_error("sign_txs() not supported");
    }

    /**
     * Submit signed transactions from a watch-only wallet.
     *
     * @param signed_tx_hex is signed transaction hex from signTxs()
     * @return the resulting transaction hashes
     */
    virtual vector<string> submit_txs(const string& signed_tx_hex) {
      throw runtime_error("submit_txs() not supported");
    }

    /**
     * Sign a message.
     *
     * @param msg is the message to sign
     * @return the signature
     */
    virtual string sign(const string& msg) const {
      throw runtime_error("sign() not supported");
    }

    /**
     * Verify a signature on a message.
     *
     * @param msg is the signed message
     * @param address is the signing address
     * @param signature is the signature
     * @return true if the signature is good, false otherwise
     */
    virtual bool verify(const string& msg, const string& address, const string& signature) const {
      throw runtime_error("verify() not supported");
    }

    /**
     * Get a transaction's secret key from its hash.
     *
     * @param tx_hash is the transaction's hash
     * @return is the transaction's secret key
     */
    virtual string get_tx_key(const string& tx_hash) const {
      throw runtime_error("get_tx_key() not supported");
    }

    /**
     * Check a transaction in the blockchain with its secret key.
     *
     * @param tx_hash specifies the transaction to check
     * @param tx_key is the transaction's secret key
     * @param address is the destination public address of the transaction
     * @return the result of the check
     */
    virtual shared_ptr<monero_check_tx> check_tx_key(const string& tx_hash, const string& tx_key, const string& address) const {
      throw runtime_error("check_tx_key() not supported");
    }

    /**
     * Get a transaction signature to prove it.
     *
     * @param tx_hash specifies the transaction to prove
     * @param address is the destination public address of the transaction
     * @param message is a message to include with the signature to further authenticate the proof (optional)
     * @return the transaction signature
     */
    virtual string get_tx_proof(const string& tx_hash, const string& address, const string& message) const {
      throw runtime_error("get_tx_proof() not supported");
    }

    /**
     * Prove a transaction by checking its signature.
     *
     * @param tx_hash specifies the transaction to prove
     * @param address is the destination public address of the transaction
     * @param message is a message included with the signature to further authenticate the proof (optional)
     * @param signature is the transaction signature to confirm
     * @return the result of the check
     */
    virtual shared_ptr<monero_check_tx> check_tx_proof(const string& tx_hash, const string& address, const string& message, const string& signature) const {
      throw runtime_error("check_tx_proof() not supported");
    }

    /**
     * Generate a signature to prove a spend. Unlike proving a transaction, it does not require the destination public address.
     *
     * @param tx_hash specifies the transaction to prove
     * @param message is a message to include with the signature to further authenticate the proof (optional)
     * @return the transaction signature
     */
    virtual string get_spend_proof(const string& tx_hash, const string& message) const {
      throw runtime_error("get_spend_proof() not supported");
    }

    /**
     * Prove a spend using a signature. Unlike proving a transaction, it does not require the destination public address.
     *
     * @param tx_hash specifies the transaction to prove
     * @param message is a message included with the signature to further authenticate the proof (optional)
     * @param signature is the transaction signature to confirm
     * @return true if the signature is good, false otherwise
     */
    virtual bool check_spend_proof(const string& tx_hash, const string& message, const string& signature) const {
      throw runtime_error("check_spend_proof() not supported");
    }

    /**
     * Generate a signature to prove the entire balance of the wallet.
     *
     * @param message is a message included with the signature to further authenticate the proof (optional)
     * @return the reserve proof signature
     */
    virtual string get_reserve_proof_wallet(const string& message) const {
      throw runtime_error("get_reserve_proof_wallet() not supported");
    }

    /**
     * Generate a signature to prove an available amount in an account.
     *
     * @param account_idx specifies the account to prove ownership of the amount
     * @param amount is the minimum amount to prove as available in the account
     * @param message is a message to include with the signature to further authenticate the proof (optional)
     * @return the reserve proof signature
     */
    virtual string get_reserve_proof_account(uint32_t account_idx, uint64_t amount, const string& message) const {
      throw runtime_error("get_reserve_proof_account() not supported");
    }

    /**
     * Proves a wallet has a disposable reserve using a signature.
     *
     * @param address is the public wallet address
     * @param message is a message included with the signature to further authenticate the proof (optional)
     * @param signature is the reserve proof signature to check
     * @return the result of checking the signature proof
     */
    virtual shared_ptr<monero_check_reserve> check_reserve_proof(const string& address, const string& message, const string& signature) const {
      throw runtime_error("check_reserve_proof() not supported");
    }

    /**
     * Get a transaction note.
     *
     * @param tx_hash specifies the transaction to get the note of
     * @return the tx note
     */
    virtual string get_tx_note(const string& tx_hash) const {
      throw runtime_error("get_tx_note() not supported");
    }

    /**
     * Get notes for multiple transactions.
     *
     * @param tx_hashes identify the transactions to get notes for
     * @preturns notes for the transactions
     */
    virtual vector<string> get_tx_notes(const vector<string>& tx_hashes) const {
      throw runtime_error("get_tx_notes() not supported");
    }

    /**
     * Set a note for a specific transaction.
     *
     * @param tx_hash specifies the transaction
     * @param note specifies the note
     */
    virtual void set_tx_note(const string& tx_hash, const string& note) {
      throw runtime_error("set_tx_note() not supported");
    }

    /**
     * Set notes for multiple transactions.
     *
     * @param tx_hashes specify the transactions to set notes for
     * @param notes are the notes to set for the transactions
     */
    virtual void set_tx_notes(const vector<string>& tx_hashes, const vector<string>& notes) {
      throw runtime_error("set_tx_notes() not supported");
    }

    /**
     * Get all address book entries.
     *
     * @param indices are indices of the entries to get
     * @return the address book entries
     */
    virtual vector<monero_address_book_entry> get_address_book_entries(const vector<uint64_t>& indices) const {
      throw runtime_error("get_address_book_entries() not supported");
    }

    /**
     * Add an address book entry.
     *
     * @param address is the entry address
     * @param description is the entry description (optional)
     * @return the index of the added entry
     */
    virtual uint64_t add_address_book_entry(const string& address, const string& description) {
      throw runtime_error("add_address_book_entry() not supported");
    }

    /**
     * Edit an address book entry.
     *
     * @param index is the index of the address book entry to edit
     * @param set_address specifies if the address should be updated
     * @param address is the updated address
     * @param set_description specifies if the description should be updated
     * @param description is the updated description
     */
    virtual void edit_address_book_entry(uint64_t index, bool set_address, const string& address, bool set_description, const string& description) {
      throw runtime_error("edit_address_book_entry() not supported");
    }

    /**
     * Delete an address book entry.
     *
     * @param index is the index of the entry to delete
     */
    virtual void delete_address_book_entry(uint64_t index) {
      throw runtime_error("delete_address_book_entry() not supported");
    }

//    /**
//     * Tag accounts.
//     *
//     * @param tag is the tag to apply to the specified accounts
//     * @param accountIndices are the indices of the accounts to tag
//     */
//    public void tagAccounts(string tag, Collection<Integer> accountIndices);
//
//    /**
//     * Untag acconts.
//     *
//     * @param accountIndices are the indices of the accounts to untag
//     */
//    public void untagAccounts(Collection<Integer> accountIndices);
//
//    /**
//     * Return all account tags.
//     *
//     * @return the wallet's account tags
//     */
//    public List<MoneroAccountTag> getAccountTags();
//
//    /**
//     * Sets a human-readable description for a tag.
//     *
//     * @param tag is the tag to set a description for
//     * @param label is the label to set for the tag
//     */
//    public void setAccountTagLabel(string tag, string label);

    /**
     * Creates a payment URI from a send configuration.
     *
     * @param request specifies configuration for a potential tx
     * @return is the payment uri
     */
    virtual string create_payment_uri(const monero_send_request& request) const {
      throw runtime_error("create_payment_uri() not supported");
    }

    /**
     * Parses a payment URI to a send request.
     *
     * @param uri is the payment uri to parse
     * @return the send request parsed from the uri
     */
    virtual shared_ptr<monero_send_request> parse_payment_uri(const string& uri) const {
      throw runtime_error("parse_payment_uri() not supported");
    }

    /**
     * Get an attribute.
     *
     * @param key is the attribute to get the value of
     * @param value is set to the key's value if set
     * @return true if the key's value has been set, false otherwise
     */
    virtual bool get_attribute(const string& key, string& value) const {
      throw runtime_error("get_attribute() not supported");
    }

    /**
     * Set an arbitrary attribute.
     *
     * @param key is the attribute key
     * @param val is the attribute value
     */
    virtual void set_attribute(const string& key, const string& val) {
      throw runtime_error("set_attribute() not supported");
    }

    /**
     * Start mining.
     *
     * @param num_threads is the number of threads created for mining (optional)
     * @param background_mining specifies if mining should occur in the background (optional)
     * @param ignore_battery specifies if the battery should be ignored for mining (optional)
     */
    virtual void start_mining(boost::optional<uint64_t> num_threads, boost::optional<bool> background_mining, boost::optional<bool> ignore_battery) {
      throw runtime_error("start_mining() not supported");
    }

    /**
     * Stop mining.
     */
    virtual void stop_mining() {
      throw runtime_error("stop_mining() not supported");
    }

    /**
     * Wait for the next block to be added to the chain.
     *
     * @return the height of the next block when it is added to the chain
     */
    virtual uint64_t wait_for_next_block() {
      throw runtime_error("wait_for_next_block() not supported");
    }

    /**
     * Indicates if importing multisig data is needed for returning a correct balance.
     *
     * @return true if importing multisig data is needed for returning a correct balance, false otherwise
     */
    virtual bool is_multisig_import_needed() const {
      throw runtime_error("is_multisig_import_needed() not supported");
    }

    // TODO: bool is_multisig()

    /**
     * Get multisig info about this wallet.
     *
     * @return multisig info about this wallet
     */
    virtual monero_multisig_info get_multisig_info() {
      throw runtime_error("get_multisig_info() not supported");
    }

    /**
     * Get multisig info as hex to share with participants to begin creating a
     * multisig wallet.
     *
     * @return this wallet's multisig hex to share with participants
     */
    virtual string prepare_multisig() {
      throw runtime_error("prepare_multisig() not supported");
    }

    /**
     * Make this wallet multisig by importing multisig hex from participants.
     *
     * @param multisig_hexes are multisig hex from each participant
     * @param threshold is the number of signatures needed to sign transfers
     * @password is the wallet password
     * @return the result which has the multisig's address xor this wallet's multisig hex to share with participants iff not N/N
     */
    virtual monero_multisig_init_result make_multisig(const vector<string>& multisig_hexes, int threshold, const string& password) {
      throw runtime_error("make_multisig() not supported");
    }

    /**
     * Exchange multisig hex with participants in a M/N multisig wallet.
     *
     * This process must be repeated with participants exactly N-M times.
     *
     * @param multisig_hexes are multisig hex from each participant
     * @param password is the wallet's password // TODO monero core: redundant? wallet is created with password
     * @return the result which has the multisig's address xor this wallet's multisig hex to share with participants iff not done
     */
    virtual  monero_multisig_init_result exchange_multisig_keys(const vector<string>& mutisig_hexes, const string& password) {
      throw runtime_error("exchange_multisig_keys() not supported");
    }

    /**
     * Export this wallet's multisig info as hex for other participants.
     *
     * @return this wallet's multisig info as hex for other participants
     */
    virtual string get_multisig_hex() {
      throw runtime_error("get_multisig_hex() not supported");
    }

    /**
     * Import multisig info as hex from other participants.
     *
     * Note: If the daemon is not trusted, this method will not automatically
     * update the spent status after importing peer multisig hex.  In that case,
     * the
     *
     * @param multisig_hexes are multisig hex from each participant
     * @return the number of outputs signed with the given multisig hex
     */
    virtual int import_multisig_hex(const vector<string>& multisig_hexes) {
      throw runtime_error("import_multisig_hex() not supported");
    }

    /**
     * Sign previously created multisig transactions as represented by hex.
     *
     * @param multisig_tx_hex is the hex shared among the multisig transactions when they were created
     * @return the result of signing the multisig transactions
     */
    virtual monero_multisig_sign_result sign_multisig_tx_hex(const string& multisig_tx_hex) {
      throw runtime_error("monero_multisig_sign_result() not supported");
    }

    /**
     * Submit signed multisig transactions as represented by a hex string.
     *
     * @param signed_multisig_tx_hex is the signed multisig hex returned from signMultisigTxs()
     * @return the resulting transaction hashes
     */
    virtual vector<string> submit_multisig_tx_hex(const string& signed_multisig_tx_hex) {
      throw runtime_error("submit_multisig_tx_hex() not supported");
    }

    /**
     * Save the wallet at its current path.
     */
    virtual void save() {
      throw runtime_error("save() not supported");
    }

    /**
     * Move the wallet from its current path to the given path.
     *
     * @param path is the new wallet's path
     * @param password is the new wallet's password
     */
    virtual void move_to(string path, string password) {
      throw runtime_error("move_to() not supported");
    }

    /**
     * Optionally save then close the wallet.
     *
     * @param save specifies if the wallet should be saved before being closed (default false)
     */
    virtual void close(bool save = false) {
      throw runtime_error("close() not supported");
    }
  };
}
