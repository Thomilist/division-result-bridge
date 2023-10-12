#ifndef __ALTEREDWIZARDPAGE_H__
#define __ALTEREDWIZARDPAGE_H__

#include <QString>
#include <QWidget>
#include <QWizardPage>

#include "../utils/ForwardDeclarations.hpp"

namespace divi
{
    class AlteredWizardPage : public QWizardPage
    {
        public:
            AlteredWizardPage(QWidget* a_parent = nullptr);
            ~AlteredWizardPage();
        
            void registerField(
                const QString& a_name,
                QWidget* a_widget,
                const char* a_property = nullptr,
                const char* a_changed_signal = nullptr);
    };
}

#endif // __ALTEREDWIZARDPAGE_H__