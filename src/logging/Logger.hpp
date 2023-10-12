#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <unordered_set>

#include <QCursor>
#include <QDateTime>
#include <QDesktopServices>
#include <QFile>
#include <QIODevice>
#include <QMouseEvent>
#include <QPlainTextEdit>
#include <QPoint>
#include <QString>
#include <QStringBuilder>
#include <QStringList>
#include <QTextStream>
#include <QWidget>

#include <cpr/cpr.h>

#include "../utils/ForwardDeclarations.hpp"

#include "../utils/Helpers.hpp"
#include "LoggerRegistry.hpp"
#include "../Settings.hpp"

#include "LoggerMode.hpp"
#include "MessageType.hpp"
#include "PrintMode.hpp"

namespace divi
{
    class Logger : public QPlainTextEdit
    {
        Q_OBJECT
        
        public:
            Logger(
                LoggerMode a_mode,
                const QString& a_name,
                Settings* a_settings,
                QWidget* a_parent = nullptr);
            ~Logger();

            const QString& registryName() const;

            int registerSignalAnchor(const QString& a_signal_anchor);
            int unregisterSignalAnchor(const QString& a_signal_anchor);

        public slots:
            void log(
                MessageType a_message_type,
                const QString& a_source,
                long a_status_code = 0,
                const QString& a_status_text = "",
                const QString& a_message = "");
            void log(
                const QString& a_source,
                const cpr::Response& a_response);
            
            void clear();
        
        signals:
            void anchorClicked(const QString& a_clicked_anchor);
            void signalAnchorClicked(const QString& a_signal_anchor);
        
        protected slots:
            virtual void anchorClickEvent(const QString& a_clicked_anchor);
        
        private:
            void mousePressEvent(QMouseEvent* a_event) override;
            void mouseReleaseEvent(QMouseEvent* a_event) override;
            void mouseMoveEvent(QMouseEvent* a_event) override;
            void setCursorOnLink(const QPoint& a_point);

            void logToFile(
                const QString& a_log_path,
                PrintMode a_log_print_mode,
                const QStringList& a_message);
            const QString excludeIfUnfit(const QString& a_body);
            const QString colorStatusText(const QString& a_message, MessageType a_message_type = MessageType::Success);
            const QString getCssStyle(MessageType a_message_type);

            LoggerMode mode;
            const QString registry_name;
            Settings* settings;
            QString clicked_anchor;
            std::unordered_set<QString> signal_anchors;
    };
}

#endif // __LOGGER_H__