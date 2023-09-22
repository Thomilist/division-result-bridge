#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>

#include <QDateTime>
#include <QPlainTextEdit>
#include <QString>
#include <QStringBuilder>
#include <QWidget>

#include <cpr/cpr.h>

#include "ForwardDeclarations.hpp"

#include "Helpers.hpp"

#include "MessageType.hpp"

namespace divi
{
    class Logger : public QPlainTextEdit
    {
        Q_OBJECT
        
        public:
            Logger(QWidget* a_parent = nullptr);
            ~Logger();

            void log(
                MessageType a_message_type,
                const QString& a_source,
                long a_status_code = 0,
                const QString& a_status_text = "",
                const QString& a_message = "");
            void log(const QString& a_source, const cpr::Response& a_response);
        
        private:
            const QString excludeIfUnfit(const QString& a_body);
            const QString colorHtmlText(const QString& a_message, MessageType a_message_type = MessageType::Info);
            const QString getColor(MessageType a_message_type);
    };
}

#endif // __LOGGER_H__