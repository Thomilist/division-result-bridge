#include "Logger.hpp"


namespace divi
{
    Logger::Logger(Settings* a_settings, QWidget* a_parent)
        : QPlainTextEdit(a_parent)
        , settings(a_settings)
    {
        setReadOnly(true);
        setMaximumBlockCount(1000);
        setTextInteractionFlags(Qt::TextBrowserInteraction);
        setMouseTracking(true);
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
            = a_source % ":"
            % (a_status_code == 0 ? QString() : (" " % QString::number(a_status_code)))
            % (a_status_text.isEmpty() ? QString() : (" " % a_status_text));

        const QStringList raw
        {
            datetime,
            status,
            a_message,
            ""
        };

        const QStringList html
        {
            "<span style=\"color: #000000; font-weight: normal;\">" % datetime % "</span>",
            colorStatusText(status, a_message_type),
            "<span class=\"color: #000000; font-weight: normal;\">" % a_message % "</span>",
            ""
        };

        for (const auto& line : html)
        {
            appendHtml(line);
        }

        if (settings->getPrettyLogging())
        {
            logToFile(settings->getHtmlLogPath(), PrintMode::HTML, html);
        }
        
        if (settings->getRawLogging())
        {
            logToFile(settings->getRawLogPath(), PrintMode::Raw, raw);
        }

        return;
    }
    
    void Logger::log(const QString& a_source, const cpr::Response& a_response)
    {
        MessageType message_type = MessageType::Success;

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
    
    void Logger::mousePressEvent(QMouseEvent* a_event)
    {
        if (a_event->button() == Qt::LeftButton)
        {
            clicked_anchor = anchorAt(a_event->pos());
        }
        else
        {
            clicked_anchor.clear();
        }

        QPlainTextEdit::mousePressEvent(a_event);
        return;
    }
    
    void Logger::mouseReleaseEvent(QMouseEvent* a_event)
    {
        if (a_event->button() == Qt::LeftButton && !clicked_anchor.isEmpty())
        {
            QString released_anchor = anchorAt(a_event->pos());

            if (clicked_anchor == released_anchor)
            {
                viewport()->setCursor(Qt::WaitCursor);
                QDesktopServices::openUrl(clicked_anchor);
                setCursorOnLink(mapFromGlobal(QCursor::pos()));
            }
        }

        QPlainTextEdit::mouseReleaseEvent(a_event);
        return;
    }
    
    void Logger::mouseMoveEvent(QMouseEvent* a_event)
    {
        setCursorOnLink(a_event->pos());
        QPlainTextEdit::mouseMoveEvent(a_event);
        return;
    }
    
    void Logger::setCursorOnLink(const QPoint& a_point)
    {
        if (!anchorAt(a_point).isEmpty())
        {
            viewport()->setCursor(Qt::PointingHandCursor);
        }
        else
        {
            viewport()->setCursor(Qt::IBeamCursor);
        }

        return;
    }
    
    void Logger::logToFile(
        const QString& a_log_path,
        PrintMode a_log_print_mode,
        const QStringList& a_message)
    {
        QFile log_file{a_log_path};

        if (log_file.open(QIODevice::Append | QIODevice::Text))
        {
            const QString linebreak = (a_log_print_mode == PrintMode::HTML ? "<br>\n" : "\n");
            QTextStream log_output{&log_file};

            for (const auto& line : a_message)
            {
                log_output << line << linebreak;
            }
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
    
    const QString Logger::colorStatusText(const QString& a_message, MessageType a_message_type)
    {
        return QString()
            % "<span style=\""
            % getCssStyle(a_message_type)
            % "\">"
            % a_message
            % "</span>";
    }
    
    const QString Logger::getCssStyle(MessageType a_message_type)
    {
        QString css_style = "color: #000000; font-weight: normal;";

        switch (a_message_type)
        {
            case MessageType::Info:
            {
                css_style = "color: #0000ff; font-weight: bold;";
                break;
            }
            case MessageType::Success:
            {
                css_style = "color: #006600; font-weight: bold;";
                break;
            }
            case MessageType::Warning:
            {
                css_style = "color: #ff6600; font-weight: bold;";
                break;
            }
            case MessageType::Error:
            {
                css_style = "color: #ff0000; font-weight: bold;";
                break;
            }
        }

        return css_style;
    }
}