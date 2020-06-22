# yalogc

yalogc is a fast, non-blocking C++ logging library for real-time and io-loop type applications

Yet another logging library for C++?
------------------------------------

The primary reason for writing this library is that existing logging facilites do blocking calls, which can be a performance detriment. For single threaded io-loop type applications (eg. web servers), blocking calls result in a considerable amout of penalty. For real-time threads also this is unacceptable since a blocking call may initiate a context-switch. So yalogc aims to provide - 

* Non-blocking logging facility for single-threaded log producers
* Non-blocking / minimally-blocking logging facility for multi-threaded log producers
* Asynchronous log consumer with or without additional threads 
* Fast and possibly low-latency logging

Additionally it should also provide -

* Modern formatting semantics similar to std::format
* Custom formatting support
* Various log targets (eg. rotating logs, syslogs, console etc)
* Level based filtering at runtime

