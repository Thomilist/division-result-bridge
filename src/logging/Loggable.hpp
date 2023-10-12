#ifndef __LOGGABLE_H__
#define __LOGGABLE_H__

#include <QString>

#include <cpr/cpr.h>

#include "../utils/ForwardDeclarations.hpp"

#include "LoggerProxy.hpp"
#include "LoggerRegistry.hpp"

#include "LoggingConcepts.hpp"

namespace divi
{
    class Loggable
    {
        friend class LoggerRegistry;
        
        public:
            virtual ~Loggable() = default;

            void log(
                MessageType a_message_type, 
                const QString& a_source,
                long a_status_code = 0,
                const QString& a_status_text = "",
                const QString& a_message = "");
            void log(const QString& a_source, const cpr::Response& a_response);
            
            const QString& registryName() const;

        protected:
            Loggable(const QString& a_name);

            template<typename LoggerRef>
                requires (CanReferToLogger<LoggerRef>)
            void attachLogging(LoggerRef a_logger)
            {
                attachLogging(this, a_logger);
                return;
            }

            template<typename LoggerRef>
                requires (CanReferToLogger<LoggerRef>)
            void detachLogging(LoggerRef a_logger)
            {
                detachLogging(this, a_logger);
                return;
            }

            template<typename LoggableRef, typename LoggerRef>
                requires (CanReferToLoggable<LoggableRef> && CanReferToLogger<LoggerRef>)
            void attachLogging(LoggableRef a_loggable, LoggerRef a_logger)
            {
                logger_proxy.queueAttachLogging(a_loggable, a_logger);
                return;
            }

            template<typename LoggableRef, typename LoggerRef>
                requires (CanReferToLoggable<LoggableRef> && CanReferToLogger<LoggerRef>)
            void detachLogging(LoggableRef a_loggable, LoggerRef a_logger)
            {
                logger_proxy.queueDetachLogging(a_loggable, a_logger);
                return;
            }
        
        private:
            LoggerProxy* loggerProxy();

            const QString registry_name;
            LoggerProxy logger_proxy;
    };
}

#endif // __LOGGABLE_H__