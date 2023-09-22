#include "Logger.hpp"


namespace divi
{
    Logger::Logger(QWidget* a_parent)
        : QPlainTextEdit(a_parent)
    {
        setReadOnly(true);
        setMaximumBlockCount(1000);
    }
    
    Logger::~Logger()
    { }
    
    void Logger::log(
        MessageType a_message_type,
        const QString& a_source,
        long a_status_code,
        const QString& a_status_text,
        const QString& a_message)
    {
        const QString datetime = QDateTime::currentDateTime().toString(Helpers::dateTimeFormat());
        const QString status
            = "<b>"
            % a_source % ":"
            % (a_status_code == 0 ? QString() : (" " % QString::number(a_status_code)))
            % (a_status_text.isEmpty() ? QString() : (" " % a_status_text))
            % "</b>";

        appendPlainText("\n" % datetime);
        appendHtml("\n" % colorHtmlText(status, a_message_type));
        appendPlainText(a_message);
        return;
    }
    
    void Logger::log(const QString& a_source, const cpr::Response& a_response)
    {
        MessageType message_type = MessageType::Info;

        if (a_response.status_code >= 400 || a_response.status_code < 100)
        {
            message_type = MessageType::Error;
        }
        else if (a_response.status_code >= 300 && a_response.status_code < 400)
        {
            message_type = MessageType::Warning;
        }
        
        if (a_response.status_code == 0)
        {
            log(
                message_type,
                a_source,
                0,
                "Request Failed",
                QString::fromStdString(a_response.error.message));
        }
        else
        {
            log(
                message_type,
                a_source,
                a_response.status_code,
                QString::fromStdString(a_response.reason),
                excludeIfUnfit(QString::fromStdString(a_response.text)));
        }

        return;
    }
    
    const QString Logger::excludeIfUnfit(const QString& a_body)
    {
        if (a_body.indexOf("<!DOCTYPE html>") == 0)
        {
            return "[HTML body excluded from log]";
        }
        else if (a_body.indexOf("<?xml") == 0)
        {
            return "[XML body excluded from log]";
        }

        return a_body;
    }
    
    const QString Logger::colorHtmlText(const QString& a_message, MessageType a_message_type)
    {
        return QString()
            % "<span style=\"color: "
            % getColor(a_message_type)
            % ";\">"
            % a_message
            % "</span>";
    }
    
    const QString Logger::getColor(MessageType a_message_type)
    {
        QString color_string = "#000000";

        switch (a_message_type)
        {
            case MessageType::Info:
            {
                color_string = "#006600";
                break;
            }
            case MessageType::Warning:
            {
                color_string = "#996600";
                break;
            }
            case MessageType::Error:
            {
                color_string = "#ff0000";
                break;
            }
        }

        return color_string;
    }
}