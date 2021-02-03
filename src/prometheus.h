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
/* ***************************** */
/* counters */
inline auto registry = std::make_shared<prometheus::Registry>();
inline auto& bandwidth_bytes_received = prometheus::BuildCounter().Name("bandwidth_bytes_received").Help("bandwidth_bytes_received").Register(*registry);
inline auto& bandwidth_bytes_sent = prometheus::BuildCounter().Name("bandwidth_bytes_sent").Help("bandwidth_bytes_sent").Register(*registry);
inline auto& transactions_size_bytes = prometheus::BuildCounter().Name("transactions_size_bytes").Help("transactions_size_bytes").Register(*registry);
inline auto& transactions_fees = prometheus::BuildCounter().Name("transactions_fees").Help("transactions_fees").Register(*registry);
inline auto& transactions_inputs = prometheus::BuildCounter().Name("transactions_inputs").Help("transactions_inputs").Register(*registry);
inline auto& transactions_outputs = prometheus::BuildCounter().Name("transactions_outputs").Help("transactions_outputs").Register(*registry);
inline auto& transactions_input_value = prometheus::BuildCounter().Name("transactions_input_value").Help("transactions_input_value").Register(*registry);
inline auto& transactions_output_value = prometheus::BuildCounter().Name("transactions_output_value").Help("transactions_output_value").Register(*registry);
inline auto& transactions_sig_ops = prometheus::BuildCounter().Name("transactions_sig_ops").Help("transactions_sig_ops").Register(*registry);
inline auto& misbehavior_amount = prometheus::BuildCounter().Name("misbehavior_amount").Help("misbehavior_amount").Register(*registry);

inline auto& BandwidthBytesReceived = bandwidth_bytes_received.Add( {{"name", "bandwidth.bytesReceived"}} );
inline auto& BandwidthBytesSent = bandwidth_bytes_sent.Add( {{"name", "bandwidth.bytesSent"}} );
inline auto& TransactionsSigOps = transactions_sig_ops.Add( {{"name", "transactions.sigOps"}} );
inline auto& TransactionsSizeBytes = transactions_size_bytes.Add( {{"name", "transactions.sizeBytes"}} );
inline auto& TransactionsFees = transactions_fees.Add( {{"name", "transactions.fees"}} );
inline auto& TransactionsInputs = transactions_inputs.Add( {{"name", "transactions.inputs"}} );
inline auto& TransactionsOutputs = transactions_outputs.Add( {{"name", "transactions.outputs"}} );
inline auto& TransactionsInputValue = transactions_input_value.Add( {{"name", "transactions.inputValue"}} );
inline auto& TransactionsOutputValue = transactions_output_value.Add( {{"name", "transactions.outputValue"}} );
inline auto& MisbehaviorAmount = misbehavior_amount.Add( {{"name", "misbehavior.amount"}} );

/* ***************************** */


/* ***************************** */
/* gauges */
inline auto& bandwidth_bytes_received_total = prometheus::BuildGauge().Name("bandwidth_bytes_received_total").Help("bandwidth_bytes_received").Register(*registry);
inline auto& bandwidth_bytes_sent_total = prometheus::BuildGauge().Name("bandwidth_bytes_sent_total").Help("bandwidth_bytes_sent").Register(*registry);
inline auto& BandwidthBytesReceivedTotal = bandwidth_bytes_received.Add( {{"name", "bandwidth.bytesReceivedTotal"}} );
inline auto& BandwidthBytesSentTotal = bandwidth_bytes_sent.Add( {{"name", "bandwidth.bytesSentTotal"}} );


inline auto& peers_total_connections = prometheus::BuildGauge().Name("peers_total_connections").Help("peers_total_connections").Register(*registry);
inline auto& peers_spv_node_connections = prometheus::BuildGauge().Name("peers_spv_node_connections").Help("peers_spv_node_connections").Register(*registry);
inline auto& peers_full_node_connections = prometheus::BuildGauge().Name("peers_full_node_connections").Help("peers_full_node_connections").Register(*registry);
inline auto& peers_inbound_connections = prometheus::BuildGauge().Name("peers_inbound_connections").Help("peers_inbound_connections").Register(*registry);
inline auto& peers_outbound_connections = prometheus::BuildGauge().Name("peers_outbound_connections").Help("peers_outbound_connections").Register(*registry);
inline auto& peers_ipv4_connections = prometheus::BuildGauge().Name("peers_ipv4_connections").Help("peers_ipv4_connections").Register(*registry);
inline auto& peers_ipv6_connections = prometheus::BuildGauge().Name("peers_ipv6_connections").Help("peers_ipv6_connections").Register(*registry);
inline auto& peers_tor_connections = prometheus::BuildGauge().Name("peers_tor_connections").Help("peers_tor_connections").Register(*registry);
inline auto& peers_connect = prometheus::BuildGauge().Name("peers_connect").Help("peers_connect").Register(*registry);
inline auto& peers_disconnect = prometheus::BuildGauge().Name("peers_disconnect").Help("peers_disconnect").Register(*registry);
inline auto& PeersTotalConnections = peers_total_connections.Add( {{"name", "peers.TotalConnections"}} );
inline auto& PeersSpvNodeConnections = peers_spv_node_connections.Add( {{"name", "peers.TotalConnections"}} );
inline auto& PeersFullNodeConnections = peers_full_node_connections.Add( {{"name", "peers.TotalConnections"}} );
inline auto& PeersInboundConnections = peers_inbound_connections.Add( {{"name", "peers.TotalConnections"}} );
inline auto& PeersOutboundConnections = peers_outbound_connections.Add( {{"name", "peers.TotalConnections"}} );
inline auto& PeersIpv4Connections = peers_ipv4_connections.Add( {{"name", "peers.TotalConnections"}} );
inline auto& PeersIpv6Connections = peers_ipv6_connections.Add( {{"name", "peers.TotalConnections"}} );
inline auto& PeersTorConnections = peers_tor_connections.Add( {{"name", "peers.TotalConnections"}} );
inline auto& PeersConnect = peers_connect.Add( {{"name", "peers.Connect"}} );
inline auto& PeersDisconnect = peers_connect.Add( {{"name", "peers.Disconnect"}} );

inline auto& fee_name = prometheus::BuildGauge().Name("fee_name").Help("fee_name").Register(*registry);
inline auto& FeeName = fee_name.Add( {{"name", "feeName"}} );

inline auto& network_exahashes_per_second = prometheus::BuildGauge().Name("network_exahashes_per_second").Help("network_exahashes_per_second").Register(*registry);
inline auto& network_difficulty = prometheus::BuildGauge().Name("network_difficulty").Help("network_difficulty").Register(*registry);
inline auto& NetworkExahashesPerSecond = network_exahashes_per_second.Add( {{"name", "network.exahashesPerSecond"}} );
inline auto& NetworkDifficulty = network_difficulty.Add( {{"name", "network.difficulty"}} );

inline auto& utxoset_tx = prometheus::BuildGauge().Name("utxoset_tx").Help("utxoset_tx").Register(*registry);
inline auto& utxoset_tx_outputs = prometheus::BuildGauge().Name("utxoset_tx_outputs").Help("utxoset_tx_outputs").Register(*registry);
inline auto& utxoset_db_size_bytes = prometheus::BuildGauge().Name("utxoset_db_size_bytes").Help("utxoset_db_size_bytes").Register(*registry);
inline auto& utxoset_block_height = prometheus::BuildGauge().Name("utxoset_block_height").Help("utxoset_block_height").Register(*registry);
inline auto& utxoset_total_btc_amount = prometheus::BuildGauge().Name("utxoset_total_btc_amount").Help("utxoset_total_btc_amount").Register(*registry);
inline auto& UtxosetTx = utxoset_tx.Add( {{"name", "utxoset.tx"}} );
inline auto& UtxosetTxOutputs = utxoset_tx_outputs.Add( {{"name", "utxoset.txOutputs"}} );
inline auto& UtxosetDbSizeBytes = utxoset_db_size_bytes.Add( {{"name", "utxoset.dbSizeBytes"}} );
inline auto& UtxosetBlockHeight = utxoset_block_height.Add( {{"name", "utxoset.blockHeight"}} );
inline auto& UtxosetTotalBTCAmount = utxoset_total_btc_amount.Add( {{"name", "utxoset.totalBTCAmount"}} );

inline auto& transactions_orphans_add = prometheus::BuildGauge().Name("transactions_orphans_add").Help("transactions_orphans_add").Register(*registry);
inline auto& transactions_orphans_remove = prometheus::BuildGauge().Name("transactions_orphans_remove").Help("transactions_orphans_remove").Register(*registry);
inline auto& transactions_orphans = prometheus::BuildGauge().Name("transactions_orphans").Help("transactions_orphans").Register(*registry);
inline auto& misbehavior_banned = prometheus::BuildGauge().Name("misbehavior_banned").Help("misbehavior_banned").Register(*registry);
// inline auto& misbehavior_amount = prometheus::BuildGauge().Name("misbehavior_amount").Help("misbehavior_amount").Register(*registry);
inline auto& peers_known_addresses = prometheus::BuildGauge().Name("peers_known_addresses").Help("peers_known_addresses").Register(*registry);
inline auto& message_received_inv_tx = prometheus::BuildGauge().Name("message_received_inv_tx").Help("message_received_inv_tx").Register(*registry);
inline auto& message_received_inv_block = prometheus::BuildGauge().Name("message_received_inv_block").Help("message_received_inv_block").Register(*registry);

inline auto& TransactionsOrphansAdd = transactions_orphans_add.Add( {{"name", "transactions.orphans.add"}} );
inline auto& TransactionsOrphansRemove = transactions_orphans_remove.Add( {{"name", "transactions.orphans.remove"}} );
inline auto& TransactionsOrphans = transactions_orphans.Add( {{"name", "transactions.orphans"}} );
inline auto& MisbehaviorBanned = misbehavior_banned.Add( {{"name", "misbehavior.banned"}} );
// inline auto& MisbehaviorAmount = misbehavior_amount.Add( {{"name", "misbehavior.amount"}} );
inline auto& PeersKnownAddresses = peers_known_addresses.Add( {{"name", "peers.knownAddresses"}} );
inline auto& MessageReceivedInvTx = message_received_inv_tx.Add( {{"name", "message.received.inv_tx"}} );
inline auto& MessageReceivedInvBlock = message_received_inv_block.Add( {{"name", "message.received.inv_block"}} );

/* ***************************** */



#endif // BITCOIN_PROMETHEUS_H
