#ifndef __LOGGABLE_H__
#define __LOGGABLE_H__

#include <QObject>

#include <cpr/cpr.h>

#include "ForwardDeclarations.hpp"

#include "Logger.hpp"
#include "LoggerProxy.hpp"

namespace divi
{
    class Loggable
    {
        public:
            virtual ~Loggable() = default;

            void setLogger(Logger* a_log);
            void log(
                MessageType a_message_type, 
                const QString& a_source,
                long a_status_code = 0,
                const QString& a_status_text = "",
                const QString& a_message = "");
            void log(const QString& a_source, const cpr::Response& a_response);

        protected:
            Loggable(Logger* a_log = nullptr, QObject* a_parent = nullptr);
        
        private:
            LoggerProxy logger_proxy;
    };
}

#endif // __LOGGABLE_H__