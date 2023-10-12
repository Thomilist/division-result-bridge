#ifndef __LOGGERREGISTRY_H__
#define __LOGGERREGISTRY_H__

#include <unordered_set>
#include <unordered_map>

#include <QObject>
#include <QOverload>
#include <QString>

#include "../utils/ForwardDeclarations.hpp"

#include "Loggable.hpp"
#include "Logger.hpp"
#include "LoggerProxy.hpp"

#include "MessageType.hpp"

namespace divi
{
    class LoggerRegistry : public QObject
    {
        Q_OBJECT

        public:
            static LoggerRegistry& instance();

            static void registerLoggable(Loggable* a_loggable);
            static void registerLoggable(Loggable* a_loggable, const QString& a_name);

            static void registerLogger(Logger* a_logger);
            static void registerLogger(Logger* a_logger, const QString& a_name);
        
        public slots:
            static int connect(Loggable* a_loggable, const QString& a_logger);
            static int connect(const QString& a_loggable, Logger* a_logger);
            static int connect(Loggable* a_loggable, Logger* a_logger);
            static int connect(const QString& a_loggable, const QString& a_logger);
            
            static int disconnect(Loggable* a_loggable, const QString& a_logger);
            static int disconnect(const QString& a_loggable, Logger* a_logger);
            static int disconnect(Loggable* a_loggable, Logger* a_logger);
            static int disconnect(const QString& a_loggable, const QString& a_logger);

        private:
            LoggerRegistry() = default;
            ~LoggerRegistry() = default;

            static void connectAttachSignals(Loggable* a_loggable);
            static void connectDetachSignals(Loggable* a_loggable);

            std::unordered_map<QString, Loggable*> loggables;
            std::unordered_map<QString, Logger*> loggers;

            std::unordered_map<QString, std::unordered_set<QString>> connections;
    };
}

#endif // __LOGGERREGISTRY_H__