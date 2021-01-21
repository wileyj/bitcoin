// https://sptci.com/docs/cpp/beastmetrics.html
//
// #include <chrono>
// #include <map>
// #include <memory>
// #include <string>
// #include <thread>
// #include <httpserver.h>
// #include <prometheus/counter.h>
// #include <prometheus/registry.h>


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

/* push */
// #include <prometheus/gateway.h>

/* pull */
#include <prometheus/exposer.h>

void StartPrometheus() {
  using namespace prometheus;
  LogPrintf("*******************    Prometheus: Starting\n");
  // int promThreads = std::max((long)gArgs.GetArg("-rpcthreads", DEFAULT_PROM_THREADS), 1L);
  LogPrintf("*******************    Prometheus: starting %d worker threads\n", 1);
  prometheus::Exposer exposer{"127.0.0.1:9153", DEFAULT_PROM_THREADS};
  LogPrintf("*******************    Exposed: port 9153\n");

  auto registry = std::make_shared<Registry>();
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
  // ask the exposer to scrape the registry on incoming scrapes
  exposer.RegisterCollectable(registry);
  for (;;) {
    LogPrintf("StopPrometheus: %d\n", stop_prom_thread);
    // LogPrintf("*******************    End of StartPrometheus Thread\n");
    if (stop_prom_thread)
      // LogPrintf("*******************    End of StartPrometheus Thread\n");
      return;
    LogPrintf("Sleeping for 1s\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // increment the counter by one (second)
    second_counter.Increment();
  }
}
