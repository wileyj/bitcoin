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
// extern bool stop_prom_thread;


void StartPrometheus();

// create structs for each type of metric we want
// auto& bandwidth_counter2 = BuildCounter()
//                            .Name("bandwidth")
//                            .Help("bandwidth_bytesReceived")
//                            .Register(*registry);
inline auto registry = std::make_shared<prometheus::Registry>();

inline auto& bandwidth_counter = prometheus::BuildCounter()
                          .Name("bandwidth")
                          .Help("bandwidth_bytesReceived")
                          .Register(*registry);
inline auto& bandwidth_bytesReceived = bandwidth_counter
                          .Add({{"name", "bytesReceived"}});
inline auto& bandwidth_bytesSent = bandwidth_counter
                          .Add( {{"name", "bytesSent"}} );

#endif // BITCOIN_PROMETHEUS_H
