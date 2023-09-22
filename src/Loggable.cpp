#include "Loggable.hpp"


namespace divi
{
    Loggable::Loggable(Logger* a_log, QObject* a_parent)
        : QObject(a_parent)
    {
        connect(
            this,
            QOverload<MessageType, const QString&, long, const QString&, const QString&>::of(&Loggable::log),
            a_log,
            QOverload<MessageType, const QString&, long, const QString&, const QString&>::of(&Logger::log));
        
        connect(
            this,
            QOverload<const QString&, const cpr::Response&>::of(&Loggable::log),
            a_log,
            QOverload<const QString&, const cpr::Response&>::of(&Logger::log));
    }
}