#ifndef BITCOIN_PROMETHEUS_H
#define BITCOIN_PROMETHEUS_H

#include <string>
#include <functional>

static const int DEFAULT_PROM_THREADS=4;
static const int DEFAULT_PROM_WORKQUEUE=16;
static const int DEFAULT_PROM_SERVER_TIMEOUT=30;
inline bool stop_prom_thread = false;
// extern bool stop_prom_thread;


void StartPrometheus();

#endif // BITCOIN_PROMETHEUS_H
