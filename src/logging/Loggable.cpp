#include "Loggable.hpp"


namespace divi
{
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
    
    const QString& Loggable::registryName() const
    {
        return registry_name;
    }

    Loggable::Loggable(const QString& a_name)
        : registry_name(a_name)
    {
        LoggerRegistry::registerLoggable(this);
    }
    
    LoggerProxy* Loggable::loggerProxy()
    {
        return &logger_proxy;
    }
}