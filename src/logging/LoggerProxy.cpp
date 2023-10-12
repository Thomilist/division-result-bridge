#include "LoggerProxy.hpp"


namespace divi
{
    LoggerProxy::~LoggerProxy()
    { }

    LoggerProxy::LoggerProxy(QObject* a_parent)
        : QObject(a_parent)
    { }
    
    void LoggerProxy::queueLog(
        MessageType a_message_type, 
        const QString& a_source,
        long a_status_code,
        const QString& a_status_text,
        const QString& a_message)
    {
        emit log
        (
            a_message_type, 
            a_source,
            a_status_code,
            a_status_text,
            a_message
        );
        
        return;
    }
    
    void LoggerProxy::queueLog(const QString& a_source, const cpr::Response& a_response)
    {
        emit log
        (
            a_source,
            a_response
        );
        
        return;
    }
}