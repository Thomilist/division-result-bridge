#ifndef __LOGGERPROXY_H__
#define __LOGGERPROXY_H__

#include <set>

#include <QObject>
#include <QString>

#include <cpr/cpr.h>

#include "../utils/ForwardDeclarations.hpp"

#include "MessageType.hpp"

#include "LoggingConcepts.hpp"

namespace divi
{
    class LoggerProxy : public QObject
    {
        Q_OBJECT

        friend class Loggable;
        
        public:
            ~LoggerProxy();

        protected:
            LoggerProxy(QObject* a_parent = nullptr);

            void queueLog(
                MessageType a_message_type, 
                const QString& a_source,
                long a_status_code = 0,
                const QString& a_status_text = "",
                const QString& a_message = "");
            void queueLog(const QString& a_source, const cpr::Response& a_response);

            template<typename LoggableRef, typename LoggerRef>
                requires (CanReferToLoggable<LoggableRef> && CanReferToLogger<LoggerRef>)
            void queueAttachLogging(LoggableRef a_loggable, LoggerRef a_logger)
            {
                emit attachLogging(a_loggable, a_logger);
                return;
            }

            template<typename LoggableRef, typename LoggerRef>
                requires (CanReferToLoggable<LoggableRef> && CanReferToLogger<LoggerRef>)
            void queueDetachLogging(LoggableRef a_loggable, LoggerRef a_logger)
            {
                emit detachLogging(a_loggable, a_logger);
                return;
            }
        
        signals:
            void log(
                MessageType a_message_type, 
                const QString& a_source,
                long a_status_code,
                const QString& a_status_text,
                const QString& a_message);
            void log(
                const QString& a_source,
                const cpr::Response& a_response);
            
            void attachLogging(Loggable* a_loggable, const QString& a_logger);
            void attachLogging(const QString& a_loggable, Logger* a_logger);
            void attachLogging(Loggable* a_loggable, Logger* a_logger);
            void attachLogging(const QString& a_loggable, const QString& a_logger);
            
            void detachLogging(Loggable* a_loggable, const QString& a_logger);
            void detachLogging(const QString& a_loggable, Logger* a_logger);
            void detachLogging(Loggable* a_loggable, Logger* a_logger);
            void detachLogging(const QString& a_loggable, const QString& a_logger);
    };
}

#endif // __LOGGERPROXY_H__