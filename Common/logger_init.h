#ifndef _LOGGER_INIT_H_
#define _LOGGER_INIT_H_

#include "logger.h"

void init_log() {
    typedef sinks::synchronous_sink <sinks::text_file_backend> TextSink;
    typedef sinks::synchronous_sink <sinks::syslog_backend> UDPSink;

    /*shared_ptr<sinks::text_ostream_backend> backend1 = boost::make_shared<sinks::text_ostream_backend>();
    backend1->add_stream(shared_ptr<std::ostream>(new std::ofstream("trace.log")));*/
    boost::shared_ptr<sinks::text_file_backend> backend1 = boost::make_shared<sinks::text_file_backend>(
            keywords::file_name = "trace_%Y-%m-%d_%H-%M-%S.log"
    );
    backend1->auto_flush(true);
    boost::shared_ptr<TextSink> sink1 = boost::make_shared<TextSink>(backend1);
    sink1->set_formatter(
            expr::format("[%1%]<%2%>(%3%): %4%")
            % expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
            % expr::attr<sign_severity_level>("Severity")
            % expr::attr<attrs::current_thread_id::value_type>("ThreadID")
            % expr::smessage
    );
    sink1->set_filter(expr::attr<sign_severity_level>("Severity") >= debug);
    logging::core::get()->add_sink(sink1);

    boost::shared_ptr<sinks::text_file_backend> backend2 = boost::make_shared<sinks::text_file_backend>(
            keywords::file_name = "trade_%Y-%m-%d_%H-%M-%S.log"
    );
    backend2->auto_flush(true);
    boost::shared_ptr<TextSink> sink2 = boost::make_shared<TextSink>(backend2);
    sink2->set_formatter(
            expr::format("%1%")
            % expr::smessage
    );
    sink2->set_filter(expr::attr<sign_severity_level>("Severity") == trade);
    logging::core::get()->add_sink(sink2);

    boost::shared_ptr<sinks::text_file_backend> backend3 = boost::make_shared<sinks::text_file_backend>(
            keywords::file_name = "portfolio_%Y-%m-%d_%H-%M-%S.log"
    );
    backend3->auto_flush(true);
    boost::shared_ptr<TextSink> sink3 = boost::make_shared<TextSink>(backend3);
    sink3->set_formatter(
            expr::format("%1%")
            % expr::smessage
    );
    sink3->set_filter(expr::attr<sign_severity_level>("Severity") == portfolio);
    logging::core::get()->add_sink(sink3);

    boost::shared_ptr<sinks::text_file_backend> backend4 = boost::make_shared<sinks::text_file_backend>(
            keywords::file_name = "data_%Y-%m-%d_%H-%M-%S.log"
    );
    backend4->auto_flush(true);
    boost::shared_ptr<TextSink> sink4 = boost::make_shared<TextSink>(backend4);
    sink4->set_formatter(
            expr::format("%1%")
            % expr::smessage
    );
    sink4->set_filter(expr::attr<sign_severity_level>("Severity") == data);
    logging::core::get()->add_sink(sink4);

    boost::shared_ptr<sinks::syslog_backend> backend_udp = boost::make_shared<sinks::syslog_backend>();
    backend_udp->set_target_address(std::string("192.168.238.1"));
    boost::shared_ptr<UDPSink> sink_udp = boost::make_shared<UDPSink>(backend_udp);
    sink_udp->set_formatter(
            expr::format("%1%")
            % expr::smessage
    );
    sink_udp->set_filter(expr::attr<sign_severity_level>("Severity") == data);
    logging::core::get()->add_sink(sink_udp);

    logging::add_common_attributes();
    logging::core::get()->add_global_attribute("ThreadID", attrs::current_thread_id());

    // write headers
    // yahoo financial api compatiable format
    datalog << "DateTime,Price,Volume";
    portfoliolog << "DateTime,Value";
    tradelog << "DateTime,Type,Symbol,Shares,Price,Cash";
}

#endif