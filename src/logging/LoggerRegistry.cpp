#include "LoggerRegistry.hpp"


namespace divi
{
    LoggerRegistry& LoggerRegistry::instance()
    {
        static LoggerRegistry instance;
        return instance;
    }
    
    void LoggerRegistry::registerLoggable(Loggable* a_loggable)
    {
        registerLoggable(a_loggable, a_loggable->registryName());
        return;
    }
    
    void LoggerRegistry::registerLoggable(Loggable* a_loggable, const QString& a_name)
    {
        // Loggable names should be known at compile-time and registration should happen at initialisation,
        // so duplicate name usage should lead to an immediate assertion failure
        assert((!instance().loggables.contains(a_name)) && "No duplicate Loggable names");

        instance().loggables.insert({a_name, a_loggable});
        instance().connections.insert({a_name, {}});

        connectAttachSignals(a_loggable);
        connectDetachSignals(a_loggable);

        return;
    }
    
    void LoggerRegistry::registerLogger(Logger* a_logger)
    {
        registerLogger(a_logger, a_logger->registryName());
        return;
    }
    
    void LoggerRegistry::registerLogger(Logger* a_logger, const QString& a_name)
    {
        // Logger names should be known at compile-time and registration should happen at initialisation,
        // so duplicate name usage should lead to an immediate assertion failure
        assert((!instance().loggers.contains(a_name)) && "No duplicate Logger names");

        instance().loggers.insert({a_name, a_logger});

        return;
    }
    
    int LoggerRegistry::connect(Loggable* a_loggable, const QString& a_logger)
    {
        return connect(a_loggable->registryName(), a_logger);
    }
    
    int LoggerRegistry::connect(const QString& a_loggable, Logger* a_logger)
    {
        return connect(a_loggable, a_logger->registryName());
    }
    
    int LoggerRegistry::connect(Loggable* a_loggable, Logger* a_logger)
    {
        return connect(a_loggable->registryName(), a_logger->registryName());
    }
    
    // Returns:
    // 0 on success
    // 1 on invalid name(s)
    // 2 if connection already exists
    // 3 on failed connection attempt
    int LoggerRegistry::connect(const QString& a_loggable, const QString& a_logger)
    {
        bool loggables_contains = instance().loggables.contains(a_loggable);
        bool loggers_contains = instance().loggers.contains(a_logger);
        
        if (!(loggables_contains && loggers_contains))
        {
            return 1;
        }

        if (instance().connections.at(a_loggable).contains(a_logger))
        {
            return 2;
        }

        if (!QObject::connect
        (
            instance().loggables.at(a_loggable)->loggerProxy(),
            QOverload<MessageType, const QString&, long, const QString&, const QString&>::of(&LoggerProxy::log),
            instance().loggers.at(a_logger),
            QOverload<MessageType, const QString&, long, const QString&, const QString&>::of(&Logger::log)
        ))
        {
            return 3;
        }

        if (!QObject::connect
        (
            instance().loggables.at(a_loggable)->loggerProxy(),
            QOverload<const QString&, const cpr::Response&>::of(&LoggerProxy::log),
            instance().loggers.at(a_logger),
            QOverload<const QString&, const cpr::Response&>::of(&Logger::log)
        ))
        {
            return 3;
        }

        instance().connections.at(a_loggable).insert(a_logger);
        return 0;
    }
    
    int LoggerRegistry::disconnect(Loggable* a_loggable, const QString& a_logger)
    {
        return disconnect(a_loggable->registryName(), a_logger);
    }
    
    int LoggerRegistry::disconnect(const QString& a_loggable, Logger* a_logger)
    {
        return disconnect(a_loggable, a_logger->registryName());
    }
    
    int LoggerRegistry::disconnect(Loggable* a_loggable, Logger* a_logger)
    {
        return disconnect(a_loggable->registryName(), a_logger->registryName());
    }
    
    // Returns:
    // 0 on success
    // 1 on invalid name(s)
    // 2 if connection doesn't already exist
    // 3 on failed disconnection attempt
    int LoggerRegistry::disconnect(const QString& a_loggable, const QString& a_logger)
    {
        if (!(instance().loggables.contains(a_loggable) && instance().loggers.contains(a_logger)))
        {
            return 1;
        }

        if (!instance().connections.at(a_loggable).contains(a_logger))
        {
            return 2;
        }

        if (!QObject::disconnect
        (
            instance().loggables.at(a_loggable)->loggerProxy(),
            QOverload<MessageType, const QString&, long, const QString&, const QString&>::of(&LoggerProxy::log),
            instance().loggers.at(a_logger),
            QOverload<MessageType, const QString&, long, const QString&, const QString&>::of(&Logger::log)
        ))
        {
            return 3;
        }

        if (!QObject::disconnect
        (
            instance().loggables.at(a_loggable)->loggerProxy(),
            QOverload<const QString&, const cpr::Response&>::of(&LoggerProxy::log),
            instance().loggers.at(a_logger),
            QOverload<const QString&, const cpr::Response&>::of(&Logger::log)
        ))
        {
            return 3;
        }

        instance().connections.at(a_loggable).erase(a_logger);
        return 0;
    }
    
    void LoggerRegistry::connectAttachSignals(Loggable* a_loggable)
    {
        QObject::connect
        (
            a_loggable->loggerProxy(),
            QOverload<const QString&, const QString&>::of(&LoggerProxy::attachLogging),
            QOverload<const QString&, const QString&>::of(&LoggerRegistry::connect)
        );

        QObject::connect
        (
            a_loggable->loggerProxy(),
            QOverload<Loggable*, const QString&>::of(&LoggerProxy::attachLogging),
            QOverload<Loggable*, const QString&>::of(&LoggerRegistry::connect)
        );
        
        QObject::connect
        (
            a_loggable->loggerProxy(),
            QOverload<const QString&, Logger*>::of(&LoggerProxy::attachLogging),
            QOverload<const QString&, Logger*>::of(&LoggerRegistry::connect)
        );
        
        QObject::connect
        (
            a_loggable->loggerProxy(),
            QOverload<Loggable*, Logger*>::of(&LoggerProxy::attachLogging),
            QOverload<Loggable*, Logger*>::of(&LoggerRegistry::connect)
        );

        return;
    }
    
    void LoggerRegistry::connectDetachSignals(Loggable* a_loggable)
    {
        QObject::connect
        (
            a_loggable->loggerProxy(),
            QOverload<const QString&, const QString&>::of(&LoggerProxy::detachLogging),
            QOverload<const QString&, const QString&>::of(&LoggerRegistry::disconnect)
        );

        QObject::connect
        (
            a_loggable->loggerProxy(),
            QOverload<Loggable*, const QString&>::of(&LoggerProxy::detachLogging),
            QOverload<Loggable*, const QString&>::of(&LoggerRegistry::disconnect)
        );
        
        QObject::connect
        (
            a_loggable->loggerProxy(),
            QOverload<const QString&, Logger*>::of(&LoggerProxy::detachLogging),
            QOverload<const QString&, Logger*>::of(&LoggerRegistry::disconnect)
        );
        
        QObject::connect
        (
            a_loggable->loggerProxy(),
            QOverload<Loggable*, Logger*>::of(&LoggerProxy::detachLogging),
            QOverload<Loggable*, Logger*>::of(&LoggerRegistry::disconnect)
        );

        return;
    }
}