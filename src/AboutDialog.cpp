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
        icon.setPixmap(QPixmap{":/icon/icon_x1024.png"}.scaledToHeight(90, Qt::SmoothTransformation));

        int layout_row = 0;
        const int icon_column = 0;
        const int key_column = 2;
        const int value_column = 4;
        const int spacer_width = 32;

        grid_layout.setColumnMinimumWidth(1, spacer_width);
        grid_layout.setColumnMinimumWidth(3, spacer_width);

        grid_layout.addWidget(&version_key, layout_row, key_column, Qt::AlignLeft);
        grid_layout.addWidget(&version_value, layout_row++, value_column, Qt::AlignRight);

        grid_layout.addWidget(&build_date_time_key, layout_row, key_column, Qt::AlignLeft);
        grid_layout.addWidget(&build_date_time_value, layout_row++, value_column, Qt::AlignRight);

        grid_layout.addWidget(&license_key, layout_row, key_column, Qt::AlignLeft);
        grid_layout.addWidget(&license_value, layout_row++, value_column, Qt::AlignRight);

        grid_layout.addWidget(&author_key, layout_row, key_column, Qt::AlignLeft);
        grid_layout.addWidget(&author_name_value, layout_row++, value_column, Qt::AlignRight);
        grid_layout.addWidget(&author_username_value, layout_row++, value_column, Qt::AlignRight);

        grid_layout.addWidget(&buttons, layout_row, 0, 1, 5, Qt::AlignCenter);
        grid_layout.addWidget(&icon, 0, icon_column, layout_row, 1, Qt::AlignCenter);

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

        return;
    }
    
    void AboutDialog::setVersionText()
    {
        version_key.setText("Version:");

        version_value.setText
        (
            QString()
            + version->getCurrentVersion()
            + " (Qt "
            + QT_VERSION_STR
            + ")"
        );

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

        license_value.setTextFormat(Qt::RichText);
        license_value.setTextInteractionFlags(Qt::TextBrowserInteraction);
        license_value.setOpenExternalLinks(true);
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

        author_username_value.setTextFormat(Qt::RichText);
        author_username_value.setTextInteractionFlags(Qt::TextBrowserInteraction);
        author_username_value.setOpenExternalLinks(true);
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

        return;
    }
    
    QString AboutDialog::getBuildDateTime()
    {
        QString build_date_time_string = QString() + __DATE__ " " + __TIME__;
        build_date_time_string.replace("  ", " ");
        QDateTime build_date_time = QLocale("en_US").toDateTime(build_date_time_string, "MMM d yyyy hh:mm:ss");
        return build_date_time.toString(Helpers::dateTimeFormat());
    }
}