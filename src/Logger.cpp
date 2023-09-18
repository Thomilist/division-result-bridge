#include "Logger.hpp"


namespace divi
{
    Logger::Logger()
    {
        setReadOnly(true);
        setMaximumBlockCount(1000);
    }
    
    Logger::~Logger()
    { }
    
    void Logger::log(
        const QString& a_source,
        long a_status_code,
        const QString& a_status_text,
        const QString& a_message)
    {
        const QString datetime = QDateTime::currentDateTime().toString(Helpers::dateTimeFormat());
        const QString status
            = a_source % ":"
            % (a_status_code == 0 ? QString() : (" " % QString::number(a_status_code)))
            % (a_status_text.isEmpty() ? QString() : (" " % a_status_text));
        
        const QString log_entry
            = "\n" % datetime
            % "\n" % status
            % (a_message.isEmpty() ? QString() : ("\n" % a_message));

        appendPlainText(log_entry);
        return;
    }
    
    void Logger::log(const QString& a_source, const cpr::Response& a_response)
    {
        if (a_response.status_code == 0)
        {
            log(
            a_source,
            0,
            "Request Failed",
            QString::fromStdString(a_response.error.message));
        }
        else
        {
            log(
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
}