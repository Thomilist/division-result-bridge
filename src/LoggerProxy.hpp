#ifndef __LOGGERPROXY_H__
#define __LOGGERPROXY_H__

#include <QObject>
#include <QOverload>

#include <cpr/cpr.h>

#include "ForwardDeclarations.hpp"

#include "Logger.hpp"

namespace divi
{
    class LoggerProxy : public QObject
    {
        Q_OBJECT
        
        public:
            LoggerProxy(QObject* a_parent = nullptr);
            ~LoggerProxy();

            void setLogger(Logger* a_log);
            void queueLog(
                MessageType a_message_type, 
                const QString& a_source,
                long a_status_code = 0,
                const QString& a_status_text = "",
                const QString& a_message = "");
            void queueLog(const QString& a_source, const cpr::Response& a_response);
        
        signals:
            void log(
                MessageType a_message_type, 
                const QString& a_source,
                long a_status_code,
                const QString& a_status_text,
                const QString& a_message);
            void log(const QString& a_source, const cpr::Response& a_response);
    };
}

#endif // __LOGGERPROXY_H__