#ifndef __COMPATIBILITYWIZARDPAGE_H__
#define __COMPATIBILITYWIZARDPAGE_H__

#include <unordered_map>

#include <QAbstractButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QString>
#include <QStringBuilder>
#include <QWidget>
#include <QWizardPage>

#include "../utils/ForwardDeclarations.hpp"

#include "../Settings.hpp"

#include "../ResultSource.hpp"

namespace divi
{
    class CompatibilityWizardPage : public QWizardPage
    {
        Q_OBJECT
        
        public:
            CompatibilityWizardPage(Settings* a_creation_settings, QWidget* a_parent = nullptr);
            ~CompatibilityWizardPage();
            
            bool isComplete() const override;

            void populate();
            void updateDescription();
        
        public slots:
            void updateSelection(QAbstractButton* a_button);
        
        private:
            Settings* creation_settings;

            QGridLayout layout;
            QLabel label;
            QButtonGroup button_group;
            std::unordered_map<QAbstractButton*, ResultSource> button_values;
            QRadioButton meos_divi_button;
            QRadioButton divi_button;
            QRadioButton xml_divi_button;
            QLabel description;
    };
}

#endif // __COMPATIBILITYWIZARDPAGE_H__