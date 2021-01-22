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
/* Define Metric Items           */
/* ***************************** */
inline auto& bandwidth_counter = prometheus::BuildCounter()
  .Name("bandwidth_counter")
  .Help("Bandwidth Counter")
  .Register(*registry);

inline auto& bandwidth_gauge = prometheus::BuildGauge()
  .Name("bandwidth_gauge")
  .Help("Bandwidth Gauge")
  .Register(*registry);
/* ***************************** */


/* ***************************** */
/* Counters                      */
/* ***************************** */
inline auto& bandwidth_bytesReceived = bandwidth_counter
  .Add({{"name", "bytesReceived"}});

inline auto& bandwidth_bytesSent = bandwidth_counter
  .Add( {{"name", "bytesSent"}} );
/* ***************************** */



/* ***************************** */
/* Gauges                        */
/* ***************************** */
inline auto& bandwidth_bytesReceivedTotal = bandwidth_gauge
  .Add( {{"name", "bytesReceivedTotal"}} );

inline auto& bandwidth_bytesSentTotal = bandwidth_gauge
  .Add( {{"name", "bytesSentTotal"}} );
/* ***************************** */


#endif // BITCOIN_PROMETHEUS_H
