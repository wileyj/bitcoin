#ifndef BITCOIN_PROMETHEUS_H
#define BITCOIN_PROMETHEUS_H
#include <string>
#include <functional>
#include <chrono>
#include <map>
#include <memory>
#include <thread>
#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>


static const int DEFAULT_PROM_THREADS=4;
static const int DEFAULT_PROM_WORKQUEUE=16;
static const int DEFAULT_PROM_SERVER_TIMEOUT=30;
inline bool stop_prom_thread = false;


void StartPrometheus();
inline auto registry = std::make_shared<prometheus::Registry>();

/* ***************************** */
/* counters */
/* ***************************** */
inline auto& bandwidth_bytes_received_total = prometheus::BuildCounter().Name("bandwidth_bytes_received_total").Help("bandwidth_bytes_received_total").Register(*registry);
inline auto& bandwidth_bytes_sent_total = prometheus::BuildCounter().Name("bandwidth_bytes_sent_total").Help("bandwidth_bytes_sent_total").Register(*registry);
inline auto& bandwidth_message_bytes_received_total = prometheus::BuildCounter().Name("bandwidth_message_bytes_received_total").Help("bandwidth_message_bytes_received_total").Register(*registry);
inline auto& bandwidth_message_bytes_sent_total = prometheus::BuildCounter().Name("bandwidth_message_bytes_sent_total").Help("bandwidth_message_bytes_sent_total").Register(*registry);
inline auto& message_received = prometheus::BuildCounter().Name("message_received").Help("message_received").Register(*registry);
inline auto& message_sent = prometheus::BuildCounter().Name("message_sent").Help("message_sent").Register(*registry);
inline auto& misbehavior_banned = prometheus::BuildCounter().Name("misbehavior_banned").Help("misbehavior_banned").Register(*registry);
inline auto& transactions_accepted = prometheus::BuildCounter().Name("transactions_accepted").Help("transactions_accepted").Register(*registry);
inline auto& transactions_fees = prometheus::BuildCounter().Name("transactions_fees").Help("transactions_fees").Register(*registry);
inline auto& transactions_input_value = prometheus::BuildCounter().Name("transactions_input_value").Help("transactions_input_value").Register(*registry);
inline auto& transactions_inputs = prometheus::BuildCounter().Name("transactions_inputs").Help("transactions_inputs").Register(*registry);
inline auto& transactions_output_value = prometheus::BuildCounter().Name("transactions_output_value").Help("transactions_output_value").Register(*registry);
inline auto& transactions_outputs = prometheus::BuildCounter().Name("transactions_outputs").Help("transactions_outputs").Register(*registry);
inline auto& transactions_sig_ops = prometheus::BuildCounter().Name("transactions_sig_ops").Help("transactions_sig_ops").Register(*registry);
inline auto& transactions_size_bytes = prometheus::BuildCounter().Name("transactions_size_bytes").Help("transactions_size_bytes").Register(*registry);
inline auto& warnings_invalid_block = prometheus::BuildCounter().Name("warnings_invalid_block").Help("warnings_invalid_block").Register(*registry);
inline auto& bandwidth_message_bytes_received = prometheus::BuildCounter().Name("bandwidth_message_bytes_received").Help("bandwidth_message_bytes_received").Register(*registry);
inline auto& bandwidth_message_bytes_sent = prometheus::BuildCounter().Name("bandwidth_message_bytes_sent").Help("bandwidth_message_bytes_sent").Register(*registry);

inline auto& BandwidthBytesReceivedTotal = bandwidth_bytes_received_total.Add({});
inline auto& BandwidthBytesSentTotal = bandwidth_bytes_sent_total.Add({});
inline auto& MisbehaviorBanned = misbehavior_banned.Add({});
inline auto& TransactionsAccepted = transactions_accepted.Add({});
inline auto& TransactionsFees = transactions_fees.Add({});
inline auto& TransactionsInputs = transactions_inputs.Add({});
inline auto& TransactionsInputValue = transactions_input_value.Add({});
inline auto& TransactionsOutputs = transactions_outputs.Add({});
inline auto& TransactionsOutputValue = transactions_output_value.Add({});
inline auto& TransactionsSigOps = transactions_sig_ops.Add({});
inline auto& TransactionsSizeBytes = transactions_size_bytes.Add({});
inline auto& WarningsInvalidBlock = warnings_invalid_block.Add({});
inline auto& BandwidthMessageBytesReceived = bandwidth_message_bytes_received.Add({});
inline auto& BandwidthMessageBytesSent = bandwidth_message_bytes_sent.Add({});

/* ***************************** */


/* ***************************** */
/* gauges */
/* ***************************** */
inline auto& accept_to_memory_pool_ms = prometheus::BuildGauge().Name("accept_to_memory_pool_ms").Help("accept_to_memory_pool_ms").Register(*registry);
inline auto& activate_best_chain_ms = prometheus::BuildGauge().Name("activate_best_chain_ms").Help("activate_best_chain_ms").Register(*registry);
inline auto& activate_block_ms = prometheus::BuildGauge().Name("activate_block_ms").Help("activate_block_ms").Register(*registry);
inline auto& bandwidth_bytes_received = prometheus::BuildGauge().Name("bandwidth_bytes_received").Help("bandwidth_bytes_received").Register(*registry);
inline auto& bandwidth_bytes_sent = prometheus::BuildGauge().Name("badwidth_bytes_sent").Help("bandwidth_bytes_sent").Register(*registry);
inline auto& block_height = prometheus::BuildGauge().Name("block_height").Help("block_height").Register(*registry);
inline auto& block_num_transations = prometheus::BuildGauge().Name("block_num_transations").Help("block_num_transations").Register(*registry);
inline auto& block_sigops = prometheus::BuildGauge().Name("block_sigops").Help("block_sigops").Register(*registry);
inline auto& block_size_bytes = prometheus::BuildGauge().Name("block_current_size_bytes").Help("block_current_size_bytes").Register(*registry);
inline auto& block_size_witness_bytes = prometheus::BuildGauge().Name("block_current_size_witness_bytes").Help("block_current_size_witness_bytes").Register(*registry);
inline auto& block_version = prometheus::BuildGauge().Name("block_version").Help("block_version").Register(*registry);
inline auto& block_weight = prometheus::BuildGauge().Name("block_weight").Help("block_weight").Register(*registry);
inline auto& check_block_us = prometheus::BuildGauge().Name("check_block_us").Help("check_block_us").Register(*registry);
inline auto& check_inputs_ms = prometheus::BuildGauge().Name("check_inputs_ms").Help("check_inputs_ms").Register(*registry);
inline auto& check_transaction_us = prometheus::BuildGauge().Name("check_transaction_us").Help("check_transaction_us").Register(*registry);
inline auto& connect_block_ms = prometheus::BuildGauge().Name("connect_block_ms").Help("connect_block_ms").Register(*registry);
inline auto& connect_tip_ms = prometheus::BuildGauge().Name("connect_tip_ms").Help("connect_tip_ms").Register(*registry);
inline auto& disconnect_block_ms = prometheus::BuildGauge().Name("disconnect_block_ms").Help("disconnect_block_ms").Register(*registry);
inline auto& fee_name = prometheus::BuildGauge().Name("fee_name").Help("fee_name").Register(*registry);
inline auto& message_received_inv_block = prometheus::BuildGauge().Name("message_received_inv_block").Help("message_received_inv_block").Register(*registry);
inline auto& message_received_inv_tx = prometheus::BuildGauge().Name("message_received_inv_tx").Help("message_received_inv_tx").Register(*registry);
inline auto& misbehavior_amount = prometheus::BuildGauge().Name("misbehavior_amount").Help("misbehavior_amount").Register(*registry);
inline auto& network_difficulty = prometheus::BuildGauge().Name("network_difficulty").Help("network_difficulty").Register(*registry);
inline auto& network_exahashes_per_second = prometheus::BuildGauge().Name("network_exahashes_per_second").Help("network_exahashes_per_second").Register(*registry);
inline auto& peers_connect = prometheus::BuildGauge().Name("peers_connect").Help("peers_connect").Register(*registry);
inline auto& peers_disconnect = prometheus::BuildGauge().Name("peers_disconnect").Help("peers_disconnect").Register(*registry);
inline auto& peers_full_node_connections = prometheus::BuildGauge().Name("peers_full_node_connections").Help("peers_full_node_connections").Register(*registry);
inline auto& peers_inbound_connections = prometheus::BuildGauge().Name("peers_inbound_connections").Help("peers_inbound_connections").Register(*registry);
inline auto& peers_ipv4_connections = prometheus::BuildGauge().Name("peers_ipv4_connections").Help("peers_ipv4_connections").Register(*registry);
inline auto& peers_ipv6_connections = prometheus::BuildGauge().Name("peers_ipv6_connections").Help("peers_ipv6_connections").Register(*registry);
inline auto& peers_known_addresses = prometheus::BuildGauge().Name("peers_known_addresses").Help("peers_known_addresses").Register(*registry);
inline auto& peers_outbound_connections = prometheus::BuildGauge().Name("peers_outbound_connections").Help("peers_outbound_connections").Register(*registry);
inline auto& peers_ping_us = prometheus::BuildGauge().Name("peers_ping_us").Help("peers_ping_us").Register(*registry);
inline auto& peers_spv_node_connections = prometheus::BuildGauge().Name("peers_spv_node_connections").Help("peers_spv_node_connections").Register(*registry);
inline auto& peers_tor_connections = prometheus::BuildGauge().Name("peers_tor_connections").Help("peers_tor_connections").Register(*registry);
inline auto& peers_total_connections = prometheus::BuildGauge().Name("peers_total_connections").Help("peers_total_connections").Register(*registry);
inline auto& transactions_duplicate = prometheus::BuildGauge().Name("transactions_duplicate").Help("transactions_duplicate").Register(*registry);
inline auto& transactions_mempool_memory_usage_bytes = prometheus::BuildGauge().Name("transactions_mempool_memory_usage_bytes").Help("transactions_mempool_memory_usage_bytes").Register(*registry);
inline auto& transactions_mempool_min_free = prometheus::BuildGauge().Name("transactions_mempool_min_free_per_kb").Help("transactions_mempool_min_free_per_kb").Register(*registry);
inline auto& transactions_mempool_total_transactions = prometheus::BuildGauge().Name("transactions_mempool_total_transactions").Help("transactions_mempool_total_transactions").Register(*registry);
inline auto& transactions_mempool_total_tx_bytes = prometheus::BuildGauge().Name("transactions_mempool_total_tx_bytes").Help("transactions_mempool_total_tx_bytes").Register(*registry);
inline auto& transactions_orphans = prometheus::BuildGauge().Name("transactions_orphans").Help("transactions_orphans").Register(*registry);
inline auto& transactions_orphans_add = prometheus::BuildGauge().Name("transactions_orphans_add").Help("transactions_orphans_add").Register(*registry);
inline auto& transactions_orphans_remove = prometheus::BuildGauge().Name("transactions_orphans_remove").Help("transactions_orphans_remove").Register(*registry);
inline auto& transactions_tx_cache_size = prometheus::BuildGauge().Name("transactions_tx_cache_size").Help("transactions_tx_cache_size").Register(*registry);
inline auto& transactions_tx_in_memory_pool = prometheus::BuildGauge().Name("transactions_tx_in_memory_pool").Help("transactions_tx_in_memory_pool").Register(*registry);
inline auto& utxoset_block_height = prometheus::BuildGauge().Name("utxoset_block_height").Help("utxoset_block_height").Register(*registry);
inline auto& utxoset_db_size_bytes = prometheus::BuildGauge().Name("utxoset_db_size_bytes").Help("utxoset_db_size_bytes").Register(*registry);
inline auto& utxoset_total_btc_amount = prometheus::BuildGauge().Name("utxoset_total_btc_amount").Help("utxoset_total_btc_amount").Register(*registry);
inline auto& utxoset_tx = prometheus::BuildGauge().Name("utxoset_tx").Help("utxoset_tx").Register(*registry);
inline auto& utxoset_tx_outputs = prometheus::BuildGauge().Name("utxoset_tx_outputs").Help("utxoset_tx_outputs").Register(*registry);
inline auto& transactions_total_count = prometheus::BuildGauge().Name("transactions_total_count").Help("transactions_total_count").Register(*registry);
inline auto& transactions_tx_rate = prometheus::BuildGauge().Name("transactions_tx_rate").Help("transactions_tx_rate").Register(*registry);

inline auto& AcceptToMemoryPoolMs = accept_to_memory_pool_ms.Add({});
inline auto& ActivateBestChainMs = activate_best_chain_ms.Add({});
inline auto& ActivateBlockMs = activate_block_ms.Add({});
inline auto& BandwidthBytesReceived = bandwidth_bytes_received.Add({});
inline auto& BandwidthBytesSent = bandwidth_bytes_sent.Add({});
inline auto& BlockHeight = block_height.Add({});
inline auto& BlockNumTransactions = block_num_transations.Add({});
inline auto& BlockSigOps = block_sigops.Add({});
inline auto& BlockSizeBytes = block_size_bytes.Add({});
inline auto& BlockSizeWitnessBytes = block_size_witness_bytes.Add({});
inline auto& BlockVersion = block_version.Add({});
inline auto& BlockWeight = block_weight.Add({});
inline auto& CheckBlockUs = check_block_us.Add({});
inline auto& CheckInputsMs = check_inputs_ms.Add({});
inline auto& CheckTransactionUs = check_transaction_us.Add({});
inline auto& ConnectBlockMs = connect_block_ms.Add({});
inline auto& ConnectTipMs = connect_tip_ms.Add({});
inline auto& DisconnectBlockMs = disconnect_block_ms.Add({});
inline auto& FeeName = fee_name.Add({});
inline auto& MessageReceivedInvBlock = message_received_inv_block.Add({});
inline auto& MessageReceivedInvTx = message_received_inv_tx.Add({});
inline auto& MisbehaviorAmount = misbehavior_amount.Add({});
inline auto& NetworkDifficulty = network_difficulty.Add({});
inline auto& NetworkExahashesPerSecond = network_exahashes_per_second.Add({});
inline auto& PeersConnect = peers_connect.Add({});
inline auto& PeersDisconnect = peers_disconnect.Add({});
inline auto& PeersFullNodeConnections = peers_full_node_connections.Add({});
inline auto& PeersInboundConnections = peers_inbound_connections.Add({});
inline auto& PeersIpv4Connections = peers_ipv4_connections.Add({});
inline auto& PeersIpv6Connections = peers_ipv6_connections.Add({});
inline auto& PeersKnownAddresses = peers_known_addresses.Add({});
inline auto& PeersOutboundConnections = peers_outbound_connections.Add({});
inline auto& PeersPingUs = peers_ping_us.Add({});
inline auto& PeersSpvNodeConnections = peers_spv_node_connections.Add({});
inline auto& PeersTorConnections = peers_tor_connections.Add({});
inline auto& PeersTotalConnections = peers_total_connections.Add({});
inline auto& TransactionsDuplicate = transactions_duplicate.Add({});
inline auto& TransactionsMempoolMemoryUsageBytes = transactions_mempool_memory_usage_bytes.Add({});
inline auto& TransactionsMempoolMinFree = transactions_mempool_min_free.Add({});
inline auto& TransactionsMempoolTotalTransactions = transactions_mempool_total_transactions.Add({});
inline auto& TransactionsMempoolTotalTXBytes = transactions_mempool_total_tx_bytes.Add({});
inline auto& TransactionsOrphans = transactions_orphans.Add({});
inline auto& TransactionsOrphansAdd = transactions_orphans_add.Add({});
inline auto& TransactionsOrphansRemove = transactions_orphans_remove.Add({});
inline auto& TransactionsTXCacheSize = transactions_tx_cache_size.Add({});
inline auto& TransactionsTxInMemoryPool = transactions_tx_in_memory_pool.Add({});
inline auto& UtxosetBlockHeight = utxoset_block_height.Add({});
inline auto& UtxosetDbSizeBytes = utxoset_db_size_bytes.Add({});
inline auto& UtxosetTotalBTCAmount = utxoset_total_btc_amount.Add({});
inline auto& UtxosetTx = utxoset_tx.Add({});
inline auto& UtxosetTxOutputs = utxoset_tx_outputs.Add({});
inline auto& TransactionsTotalCount = transactions_total_count.Add({});
inline auto& TransactionsTxRate = transactions_tx_rate.Add({});

/* ***************************** */

#endif // BITCOIN_PROMETHEUS_H
