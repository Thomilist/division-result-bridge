#ifndef __CONFIGVALIDATOR_H__
#define __CONFIGVALIDATOR_H__

#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <QString>
#include <QStringBuilder>

#include "ForwardDeclarations.hpp"

#include "Helpers.hpp"
#include "Loggable.hpp"
#include "Logger.hpp"
#include "Settings.hpp"

#include "MessageType.hpp"

namespace divi
{
    class ConfigValidator : public Loggable
    {
        Q_OBJECT

        public:
            ConfigValidator(
                Logger* a_log,
                Settings* a_settings,
                QObject* a_parent = nullptr);
            ~ConfigValidator();

            bool validate();
        
        private:
            bool divisionPathsValid();
            bool workingDirValid();
            bool diviExePathValid();

            Settings* settings;
    };
}

#endif // __CONFIGVALIDATOR_H__