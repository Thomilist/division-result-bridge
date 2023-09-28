#include "Loggable.hpp"


namespace divi
{
    Loggable::Loggable(Logger* a_log, QObject* a_parent)
        : logger_proxy(a_parent)
    {
        setLogger(a_log);
    }

    void Loggable::setLogger(Logger* a_log)
    {
        logger_proxy.setLogger(a_log);
        return;
    }
    
    void Loggable::log(
        MessageType a_message_type, 
        const QString& a_source,
        long a_status_code,
        const QString& a_status_text,
        const QString& a_message)
    {
        logger_proxy.queueLog(
            a_message_type, 
            a_source,
            a_status_code,
            a_status_text,
            a_message);
        
        return;
    }
    
    void Loggable::log(const QString& a_source, const cpr::Response& a_response)
    {
        logger_proxy.queueLog(a_source, a_response);
        return;
    }
}