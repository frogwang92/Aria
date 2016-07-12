# Aria
C++ based backtest platform

- C++ and Python mix programming with boost::Python.
- Datafeed and Algorithm can be implement in Python.
	Because of Python GIL, if Datafeed and Algorithm are both Python code, performance may be affected on multi core CPU.
- Support OHLCV data.
- A simple GUI based on amcharts.

TODO
------------
- Tick data(realtime) support.
- FIX protocol support.
- More indicators.
- More algorithms.
- Cross platform build.

Boost library dependencies
------------
boost_chrono
boost_date_time
boost_file_system
boost_log
boost_python
boost_system
boost_thread