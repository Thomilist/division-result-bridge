#ifndef __ABOUTDIALOG_H__
#define __ABOUTDIALOG_H__

#include <array>

#include <QDateTime>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QLocale>
#include <QPixmap>
#include <QString>
#include <QStringBuilder>
#include <QWidget>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <pugixml.hpp>

#include "utils/ForwardDeclarations.hpp"

#include "utils/Helpers.hpp"
#include "version/Version.hpp"

namespace divi
{
    class AboutDialog : public QDialog
    {
        Q_OBJECT

        public:
            AboutDialog(Version* a_version, QWidget* a_parent = nullptr);
            ~AboutDialog();

        public slots:
            void open() override;
        
        private:
            void setText();
            void setVersionText();
            void setBuildDateTimeText();
            void setLicenseText();
            void setAuthorText();
            void setExternalResourcesText();
            void setBuiltWithText();
            const QString getBuildDateTime();
            const QString getPuxiXmlVersionString();
            const QString getNlohmannJsonVersionString();

            Version* version;
            QGridLayout grid_layout;
            QDialogButtonBox buttons;
            std::array<QFrame, 3> divider_lines;

            QLabel icon;

            QLabel version_key;
            QLabel version_value;

            QLabel build_date_time_key;
            QLabel build_date_time_value;

            QLabel license_key;
            QLabel license_value;

            QLabel author_key;
            QLabel author_name_value;
            QLabel author_email_value;
            QLabel author_username_value;
            QLabel author_club_value;

            QLabel external_resources_key;
            QLabel divisionsmatch_value;
            QLabel meos_value;
            QLabel iof_xml_value;
            QLabel liveresults_value;

            QLabel built_with_key;
            QLabel qt_version_value;
            QLabel libcpr_version_value;
            QLabel libcurl_version_value;
            QLabel pugixml_version_value;
            QLabel nlohmann_json_version_value;
            QLabel icons_value;
    };
}

#endif // __ABOUTDIALOG_H__