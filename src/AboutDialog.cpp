#include "AboutDialog.hpp"


namespace divi
{
    AboutDialog::AboutDialog(Version* a_version, QWidget* a_parent)
        : QDialog(a_parent, QDialog().windowFlags() & ~Qt::WindowContextHelpButtonHint)
        , version(a_version)
        , buttons(QDialogButtonBox::Close)
    {
        setModal(true);
        setWindowTitle("About " % Helpers::projectName());
        
        connect(&buttons, &QDialogButtonBox::rejected, this, &QDialog::accept);

        setText();
        icon.setPixmap(QPixmap{":/icon/icon_v3.png"}.scaledToHeight(128, Qt::SmoothTransformation));
        icon.setStyleSheet("border: 1px solid gray");

        for (auto& divider : divider_lines)
        {
            divider.setLineWidth(1);
            divider.setFrameStyle(QFrame::HLine | QFrame::Plain);
        }

        for (auto label :
        {
            &version_value,
            &build_date_time_value,
            &license_value,
            &author_name_value,
            &author_email_value,
            &author_username_value,
            &author_club_value,
            &divisionsmatch_value,
            &meos_value,
            &iof_xml_value,
            &liveresults_value,
            &qt_version_value,
            &libcpr_version_value,
            &libcurl_version_value,
            &pugixml_version_value,
            &nlohmann_json_version_value,
            &icons_value
        })
        {
            label->setTextFormat(Qt::RichText);
            label->setTextInteractionFlags(Qt::TextBrowserInteraction);
            label->setOpenExternalLinks(true);
        }

        int layout_row = 0;
        const int icon_column = 0;
        const int key_column = 2;
        const int value_column = 4;
        const int spacer_width = 24;
        int divider_index = 0;

        grid_layout.setColumnMinimumWidth(1, 0);
        grid_layout.setColumnMinimumWidth(3, spacer_width);

        grid_layout.addWidget(&version_key, layout_row, key_column, Qt::AlignLeft);
        grid_layout.addWidget(&version_value, layout_row++, value_column, Qt::AlignRight);

        grid_layout.addWidget(&build_date_time_key, layout_row, key_column, Qt::AlignLeft);
        grid_layout.addWidget(&build_date_time_value, layout_row++, value_column, Qt::AlignRight);

        grid_layout.addWidget(&license_key, layout_row, key_column, Qt::AlignLeft);
        grid_layout.addWidget(&license_value, layout_row++, value_column, Qt::AlignRight);

        grid_layout.setRowMinimumHeight(layout_row, spacer_width);
        grid_layout.addWidget(&divider_lines[divider_index++], layout_row++, key_column, 1, (value_column - key_column + 1), Qt::AlignVCenter);

        grid_layout.addWidget(&author_key, layout_row, key_column, Qt::AlignLeft);
        grid_layout.addWidget(&author_name_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&author_email_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&author_username_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&author_club_value, layout_row++, value_column, Qt::AlignRight);
        
        grid_layout.setRowMinimumHeight(layout_row, spacer_width);
        grid_layout.addWidget(&divider_lines[divider_index++], layout_row++, key_column, 1, (value_column - key_column + 1), Qt::AlignVCenter);

        grid_layout.addWidget(&external_resources_key, layout_row, key_column, Qt::AlignLeft);
        
        grid_layout.addWidget(&divisionsmatch_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&meos_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&iof_xml_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&liveresults_value, layout_row++, value_column, Qt::AlignRight);
        
        grid_layout.setRowMinimumHeight(layout_row, spacer_width);
        grid_layout.addWidget(&divider_lines[divider_index++], layout_row++, key_column, 1, (value_column - key_column + 1), Qt::AlignVCenter);

        grid_layout.addWidget(&built_with_key, layout_row, key_column, Qt::AlignLeft);

        grid_layout.addWidget(&qt_version_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&libcpr_version_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&libcurl_version_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&pugixml_version_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&nlohmann_json_version_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&icons_value, layout_row++, value_column, Qt::AlignRight);

        grid_layout.setRowMinimumHeight(layout_row++, spacer_width);

        grid_layout.addWidget(&buttons, layout_row, 0, 1, 5, Qt::AlignCenter);
        grid_layout.addWidget(&icon, 0, icon_column, layout_row, 1, Qt::AlignTop | Qt::AlignHCenter);

        grid_layout.setVerticalSpacing(0);
        setLayout(&grid_layout);
        layout()->setSizeConstraint(QLayout::SetFixedSize);
    }
    
    AboutDialog::~AboutDialog()
    { }
    
    void AboutDialog::open()
    {
        QDialog::open();
        return;
    }
    
    void AboutDialog::setText()
    {
        setVersionText();
        setBuildDateTimeText();
        setLicenseText();
        setAuthorText();
        setExternalResourcesText();
        setBuiltWithText();

        return;
    }
    
    void AboutDialog::setVersionText()
    {
        version_key.setText("Version:");
        version_value.setText(version->getCurrentVersion());

        return;
    }
    
    void AboutDialog::setBuildDateTimeText()
    {
        build_date_time_key.setText("Build date:");

        build_date_time_value.setText
        (
            getBuildDateTime()
        );

        return;
    }
    
    void AboutDialog::setLicenseText()
    {
        license_key.setText("License:");

        license_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % Helpers::gitHubLicenseUrl()
            % "\">"
            % "MIT License"
            % "</a>"
        );

        return;
    }
    
    void AboutDialog::setAuthorText()
    {
        author_key.setText("Author:");

        author_name_value.setText(Helpers::authorName());

        author_email_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\"mailto:"
            % Helpers::authorEmail()
            % "?subject="
            % Helpers::prettyProjectName()
            % "\">"
            % Helpers::authorEmail()
            % "</a>"
        );

        author_username_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % Helpers::gitHubUserUrl()
            % "\">"
            % "@"
            % Helpers::gitHubUsername()
            % "</a>"
        );

        author_club_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % Helpers::authorClubDomain()
            % "\">"
            % Helpers::authorClub()
            % "</a>"
        );

        return;
    }
    
    void AboutDialog::setExternalResourcesText()
    {
        external_resources_key.setText("External resources:");

        divisionsmatch_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % Helpers::diviGitHubRepoUrl()
            % "\">"
            % Helpers::diviNameLong()
            % "</a>"
        );

        meos_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % Helpers::meosUrl()
            % "\">"
            % Helpers::meosName()
            % "</a>"
        );

        iof_xml_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % "https://orienteering.sport/iof/it/data-standard-3-0/"
            % "\">"
            % "IOF XML"
            % "</a>"
        );

        liveresults_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % "https://liveresultat.orientering.se/?lang=en"
            % "\">"
            % "liveresultat.orientering.se"
            % "</a>"
        );

        return;
    }
    
    void AboutDialog::setBuiltWithText()
    {
        built_with_key.setText("Built with:");

        qt_version_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % "https://www.qt.io/"
            % "\">"
            % "Qt "
            % QT_VERSION_STR
            % "</a>"
        );

        libcpr_version_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % "https://docs.libcpr.org/"
            % "\">"
            % "libcpr "
            % CPR_VERSION
            % "</a>"
        );

        libcurl_version_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % "https://curl.se/"
            % "\">"
            % "libcurl "
            % LIBCURL_VERSION
            % "</a>"
        );

        pugixml_version_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % "https://pugixml.org/"
            % "\">"
            % "pugixml "
            % getPuxiXmlVersionString()
            % "</a>"
        );

        nlohmann_json_version_value.setText
        (
            QString()
            % "<a style=\"color:#1d99f3\" href=\""
            % "https://json.nlohmann.me/"
            % "\">"
            % "nlohmann/json "
            % getNlohmannJsonVersionString()
            % "</a>"
        );

        icons_value.setText
        (
            QString()
            % "Icons by "
            % "<a style=\"color:#1d99f3\" href=\""
            % "https://icons8.com/"
            % "\">"
            % "Icons8"
            % "</a>"
        );

        return;
    }
    
    const QString AboutDialog::getBuildDateTime()
    {
        QString build_date_time_string = QString() + __DATE__ " " + __TIME__;
        build_date_time_string.replace("  ", " ");
        QDateTime build_date_time = QLocale("en_US").toDateTime(build_date_time_string, "MMM d yyyy hh:mm:ss");
        return build_date_time.toString(Helpers::dateTimeFormat());
    }
    
    const QString AboutDialog::getPuxiXmlVersionString()
    {
        int combined_version = PUGIXML_VERSION;

        int major = combined_version / 1000;
        int minor = (combined_version - major * 1000) / 10;
        int patch = combined_version - major * 1000 - minor * 10;

        return QString()
            % QString::number(major)
            % "."
            % QString::number(minor)
            % "."
            % QString::number(patch);
    }
    
    const QString AboutDialog::getNlohmannJsonVersionString()
    {
        return QString()
            % QString::number(NLOHMANN_JSON_VERSION_MAJOR)
            % "."
            % QString::number(NLOHMANN_JSON_VERSION_MINOR)
            % "."
            % QString::number(NLOHMANN_JSON_VERSION_PATCH);
    }
}