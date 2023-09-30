#ifndef __ABOUTDIALOG_H__
#define __ABOUTDIALOG_H__

#include <QDebug>

#include <QDateTime>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QLocale>
#include <QPixmap>
#include <QString>
#include <QStringBuilder>
#include <QWidget>

#include "ForwardDeclarations.hpp"

#include "Helpers.hpp"
#include "Version.hpp"

namespace divi
{
    class AboutDialog : public QDialog
    {
        Q_OBJECT

        public:
            AboutDialog(Version* a_version, QWidget* a_parent = nullptr);
            ~AboutDialog();

        public slots:
            void open();
        
        private:
            void setText();
            void setVersionText();
            void setBuildDateTimeText();
            void setLicenseText();
            void setAuthorText();
            QString getBuildDateTime();

            Version* version;
            QGridLayout grid_layout;
            QDialogButtonBox buttons;

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
    };
}

#endif // __ABOUTDIALOG_H__