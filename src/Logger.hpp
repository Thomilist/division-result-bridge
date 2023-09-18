#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>

#include <QDateTime>
#include <QPlainTextEdit>
#include <QString>
#include <QStringBuilder>

#include <cpr/cpr.h>

#include "ForwardDeclarations.hpp"

#include "Helpers.hpp"

namespace divi
{
    class Logger : public QPlainTextEdit
    {
        Q_OBJECT
        
        public:
            Logger();
            ~Logger();

            void log(
                const QString& a_source,
                long a_status_code = 0,
                const QString& a_status_text = "",
                const QString& a_message = "");
            void log(const QString& a_source, const cpr::Response& a_response);
        
        private:
            const QString excludeIfUnfit(const QString& a_body);
    };
}

#endif // __LOGGER_H__