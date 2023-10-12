#ifndef __COMPETITIONCREATIONWIZARD_H__
#define __COMPETITIONCREATIONWIZARD_H__

#include <optional>
#include <unordered_map>

#include <QAbstractItemView>
#include <QButtonGroup>
#include <QCheckBox>
#include <QClipboard>
#include <QDesktopServices>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QGuiApplication>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QRadioButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSize>
#include <QSizePolicy>
#include <QString>
#include <QStringBuilder>
#include <QTableView>
#include <QTimer>
#include <QWidget>
#include <QWizardPage>
#include <QWizard>

#include "../utils/ForwardDeclarations.hpp"

#include "AlteredWizardPage.hpp"
#include "../Competition.hpp"
#include "../utils/Helpers.hpp"
#include "../logging/Loggable.hpp"
#include "../logging/Logger.hpp"
#include "../logging/LoggerRegistry.hpp"
#include "ResponseWizardPage.hpp"
#include "../Settings.hpp"
#include "SummaryTableModel.hpp"

#include "../logging/LoggerMode.hpp"
#include "../ResultSource.hpp"

namespace divi
{
    class CompetitionCreationWizard : public QWizard, public Loggable
    {
        Q_OBJECT
        
        public:
            enum Page : unsigned int
            {
                Introduction,
                Compatibility,
                Password,
                Server,
                Response,
                Summary,
                _Count
            };

            CompetitionCreationWizard(Settings* a_settings, QWidget* a_parent = nullptr);
            ~CompetitionCreationWizard();

        signals:
            void requestNewCompetition(const Settings& a_request_settings);
            void useNewCompetition(Settings& a_new_settings);
        
        public slots:
            void open();
            void receiveNewCompetition(std::optional<Settings> a_response_settings);
        
        private slots:
            void receiveSignalAnchor(const QString& a_signal_anchor);
            void updateCompatibilitySelection(QAbstractButton* a_button);
            void pageChanged(int a_page_id);
            void copySummary();
        
        private:
            void accept() override;
            void done(int a_result) override;

            void createIntroductionPage();
            void createCompatibilityPage();
            void createPasswordPage();
            void createServerPage();
            void createResponsePage();
            void createSummaryPage();

            void populate();
            const QString pageNumber(Page a_page);
            void updateCompatibilityDescription();
            void initiateRequest();

            Settings* settings;
            Settings creation_settings;
            Settings last_creation_settings;
            bool first_launch = true;
            Logger* logger;

            // Introduction page
            QWizardPage introduction_page;
            QGridLayout introduction_page_layout;
            QLabel introduction_label;

            // Compatibility page
            QWizardPage compatibility_page;
            QGridLayout compatibility_page_layout;
            QLabel compatibility_label;
            QButtonGroup compatibility_button_group;
            std::unordered_map<QAbstractButton*, ResultSource> compatibility_button_values;
            QRadioButton meos_divi_button;
            QRadioButton divi_button;
            QRadioButton xml_divi_button;
            QLabel compatibility_description;

            // Password page
            AlteredWizardPage password_page;
            QGridLayout password_page_layout;
            QLabel password_label;
            QLineEdit password_input;
            QRegularExpression password_regex;
            QRegularExpressionValidator password_validator;
            QGroupBox password_disclaimer_group;
            QGridLayout password_disclaimer_layout;
            QLabel password_disclaimer_icon;
            QLabel password_disclaimer_label;

            // Server / request page
            AlteredWizardPage server_page;
            QGridLayout server_page_layout;
            QLabel server_label;
            QGridLayout server_address_layout;
            QLineEdit server_address_input;
            QPushButton server_address_use_current_button;
            QPushButton server_address_use_last_button;
            QLabel server_request_label;

            // Response page
            ResponseWizardPage response_page;
            static const QString request_again_anchor;

            // Summary page
            QWizardPage summary_page;
            QGridLayout summary_page_layout;
            QLabel summary_label;
            QTableView summary_table;
            SummaryTableModel summary_table_model;
            QPushButton summary_copy_button;
            QGridLayout summary_checkbox_layout;
            QCheckBox summary_use_now_checkbox;
            QLabel summary_copy_label;
            QTimer summary_copy_label_timer;
    };
}

#endif // __COMPETITIONCREATIONWIZARD_H__