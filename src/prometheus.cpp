// https://sptci.com/docs/cpp/beastmetrics.html
#include <logging.h>
#include <util/system.h>
#include <support/events.h>

#include <prometheus/counter.h>
#include <prometheus/registry.h>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <sys/param.h>
#include <unistd.h>
#include <prometheus.h>
#include <mutex>

/* push */
// #include <prometheus/gateway.h>

/* pull */
#include <prometheus/exposer.h>


void StartPrometheus() {
  using namespace prometheus;
  std::mutex mutex;
  LogPrintf("Prometheus Server: starting %d worker threads\n", 1);
  prometheus::Exposer exposer{"127.0.0.1:9153", DEFAULT_PROM_THREADS};

  // auto registry = std::make_shared<Registry>();
  // add a new counter family to the registry (families combine values with the
  // same name, but distinct label dimensions)
  auto& counter_family = BuildCounter()
                             .Name("time_running_seconds_total")
                             .Help("How many seconds is this server running?")
                             .Labels({{"label", "value"}})
                             .Register(*registry);

  // add a counter to the metric family
  auto& second_counter = counter_family.Add(
      {{"another_label", "value"}, {"yet_another_label", "value"}});

  // auto& bandwidth_counter = BuildCounter()
  //                            .Name("bandwidth")
  //                            .Help("bandwidth_bytesReceived")
  //                            .Register(*registry);
  // auto& bandwidth_bytesReceived = bandwidth_counter.Add(
  //     {{"name", "bytesReceived"}});
  // auto& bandwidth_bytesSent = bandwidth_counter.Add(
  //     {{"name", "bytesSent"}});
  // bandwidth_bytesSent.Increment(13);
  // bandwidth_bytesReceived.Increment(18);

  // ask the exposer to scrape the registry on incoming scrapes
  exposer.RegisterCollectable(registry);
  mutex.lock();
  for (;;) {
    if (stop_prom_thread)
      break;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // increment the counter by one (second)
    second_counter.Increment();
  }
  mutex.unlock();
  return;
}
