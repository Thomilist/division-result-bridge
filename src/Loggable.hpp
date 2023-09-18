#ifndef __LOGGABLE_H__
#define __LOGGABLE_H__

#include <QObject>
#include <QOverload>

#include <cpr/cpr.h>

#include "ForwardDeclarations.hpp"

#include "Logger.hpp"

namespace divi
{
    class Loggable : public QObject
    {
        Q_OBJECT
        
        public:
            virtual ~Loggable() = default;
        
        signals:
            void log(
                const QString& a_source,
                long a_status_code = 0,
                const QString& a_status_text = "",
                const QString& a_message = "");
            void log(const QString& a_source, const cpr::Response& a_response);
        
        protected:
            Loggable(Logger* a_log, QObject* a_parent = nullptr);
    };
}
#endif // __LOGGABLE_H__