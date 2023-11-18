#include "CompetitionCreationWizard.hpp"


namespace divi
{
    const QString CompetitionCreationWizard::request_again_anchor = "signal:request-again";
    
    CompetitionCreationWizard::CompetitionCreationWizard(Settings* a_settings, QWidget* a_parent)
        : QWizard(a_parent)
        , Loggable(Helpers::loggableCompetitionCreationWizard())
        , settings(a_settings)
        , logger(new Logger(
            LoggerMode::Widget,
            Helpers::loggerCompetitionCreationWizard(),
            settings,
            this))
        , compatibility_page(&creation_settings, this)
        , response_page(logger, this)
    {
        setModal(true);
        setWindowTitle("Create New Competition");
        setWizardStyle(QWizard::ModernStyle);

        setOptions
        ({
            QWizard::IndependentPages,
            QWizard::NoBackButtonOnStartPage,
            QWizard::NoBackButtonOnLastPage,
            QWizard::HaveHelpButton,
            QWizard::NoCancelButtonOnLastPage
        });
        
        creation_settings.setWebserverAddress(settings->getWebserverAddress());

        createIntroductionPage();
        createCompatibilityPage();
        createPasswordPage();
        createServerPage();
        createResponsePage();
        createSummaryPage();

        connect(this, &QWizard::helpRequested, []
        {
            QDesktopServices::openUrl(QUrl{Helpers::gitHubWikiUrl() % "Create-your-competition", QUrl::TolerantMode});
        });

        connect(this, &CompetitionCreationWizard::currentIdChanged, this, &CompetitionCreationWizard::pageChanged);

        attachLogging(logger);
        attachLogging(Helpers::loggerFile());

        logger->registerSignalAnchor(request_again_anchor);
        connect(logger, &Logger::signalAnchorClicked, this, &CompetitionCreationWizard::receiveSignalAnchor);
    }
    
    CompetitionCreationWizard::~CompetitionCreationWizard()
    { }
    
    void CompetitionCreationWizard::open()
    {
        logger->clear();
        attachLogging(Helpers::loggableWebserverInterface(), logger);
        detachLogging(Helpers::loggableWebserverInterface(), Helpers::loggerMain());

        restart();
        populate();
        show();

        first_launch = false;
        return;
    }
    
    void CompetitionCreationWizard::receiveNewCompetition(std::optional<Settings> a_response_settings)
    {
        button(QWizard::BackButton)->setDisabled(false);
        
        if (a_response_settings.has_value())
        {
            creation_settings = a_response_settings.value();
            response_page.setCompetitionReceived(true);
            next();
        }
        else
        {
            log(MessageType::Info, "Internal / Create New", 0, "Troubleshooting",
                QString()
                % "It appears someting went wrong. Here are a few things you can try:"
                % "<ul>"
                    % "<li>&bull; Ensure that the address specified on the previous page is correct</li>"
                    % "<li>&bull; Check your internet connection</li>"
                    % "<li>&bull; Verify that the server is online</li>"
                    % "<li>&bull; <a href=\"" % request_again_anchor % "\">Send the request again</a></li>"
                % "</ul>");
        }
        
        return;
    }
    
    void CompetitionCreationWizard::receiveSignalAnchor(const QString& a_signal_anchor)
    {
        if (a_signal_anchor == request_again_anchor)
        {
            initiateRequest();
        }

        return;
    }
    
    void CompetitionCreationWizard::pageChanged(int a_page_id)
    {
        switch (a_page_id)
        {
            case Page::Response:
            {
                initiateRequest();
                break;
            }
            case Page::Summary:
            {
                summary_table_model.updateData(creation_settings);
                summary_table.resizeColumnsToContents();
                break;
            }
            default:
            {
                break;
            }
        }
        
        return;
    }
    
    void CompetitionCreationWizard::copySummary()
    {
        QClipboard* clipboard = QGuiApplication::clipboard();

        const QString server_address_key = summary_table_model.index(0, 0).data().toString();
        const QString server_address_value = summary_table_model.index(0, 1).data().toString();
        const QString competition_id_key = summary_table_model.index(1, 0).data().toString();
        const QString competition_id_value = summary_table_model.index(1, 1).data().toString();
        const QString password_key = summary_table_model.index(2, 0).data().toString();
        const QString password_value = summary_table_model.index(2, 1).data().toString();

        clipboard->setText
        (
            QString()
            % Helpers::prettyProjectName() % " configuration"
            % "\n"
            % server_address_key % "\t" % server_address_value
            % "\n"
            % competition_id_key % "\t" % competition_id_value
            % "\n"
            % password_key % "\t" % password_value
        );

        summary_copy_label.setVisible(true);
        summary_copy_label_timer.start(2500);

        return;
    }
    
    void CompetitionCreationWizard::accept()
    {
        if (summary_use_now_checkbox.isChecked())
        {
            emit useNewCompetition(creation_settings);
        }

        QWizard::accept();
        return;
    }
    
    void CompetitionCreationWizard::done(int a_result)
    {
        detachLogging(Helpers::loggableWebserverInterface(), logger);
        attachLogging(Helpers::loggableWebserverInterface(), Helpers::loggerMain());

        last_creation_settings = creation_settings;

        QWizard::done(a_result);
        return;
    }
    
    void CompetitionCreationWizard::createIntroductionPage()
    {
        introduction_page.setTitle("Introduction " % pageNumber(Page::Introduction));
        introduction_page.setSubTitle("Create a new competition");

        introduction_label.setWordWrap(true);
        introduction_label.setText("This wizard will help you create a new competition. Don't worry - it's quick and easy.");

        introduction_page_layout.addWidget(&introduction_label, 0, 0);

        introduction_page.setLayout(&introduction_page_layout);
        setPage(Page::Introduction, &introduction_page);
        return;
    }
    
    void CompetitionCreationWizard::createCompatibilityPage()
    {
        compatibility_page.setTitle("Compatibility " % pageNumber(Page::Compatibility));
        compatibility_page.setSubTitle("Select a result source according to your surrounding setup");

        setPage(Page::Compatibility, &compatibility_page);
        return;
    }

    void CompetitionCreationWizard::createPasswordPage()
    {
        password_page.setTitle("Password " % pageNumber(Page::Password));
        password_page.setSubTitle("Choose a password for your competition");
        
        password_label.setWordWrap(true);
        password_label.setText(
            QString()
            % "You will need a password in order to change the settings of your competition and to upload results. "
            % "Choose carefully, as it cannot be changed later. ");
        
        password_regex.setPattern(Helpers::passwordRegex());
        password_validator.setRegularExpression(password_regex);
        password_input.setValidator(&password_validator);
        password_page.registerField("password*", &password_input);
        password_input.setToolTip(
            "Not secure. Seriously, don't reuse a password from another service. Act as if the whole world can see it, because, well, it can");

        password_disclaimer_icon.setPixmap(QPixmap{":/icon/icons8-warning-96.png"}.scaledToHeight(48, Qt::SmoothTransformation));

        password_disclaimer_label.setTextFormat(Qt::RichText);
        password_disclaimer_label.setWordWrap(true);
        password_disclaimer_label.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        password_disclaimer_label.setText(Helpers::passwordDisclaimer());

        int layout_row = 0;

        password_page_layout.addWidget(&password_label, layout_row++, 0);

        password_page_layout.setRowMinimumHeight(layout_row++, 10);

        password_page_layout.addWidget(&password_input, layout_row++, 0);

        password_page_layout.setRowMinimumHeight(layout_row++, 10);

        password_disclaimer_layout.addWidget(&password_disclaimer_icon, 0, 0);
        password_disclaimer_layout.addWidget(&password_disclaimer_label, 0, 1);
        password_disclaimer_group.setLayout(&password_disclaimer_layout);
        password_page_layout.addWidget(&password_disclaimer_group, layout_row++, 0);

        password_page.setLayout(&password_page_layout);

        connect(&password_input, &QLineEdit::textChanged, this, [this](const QString& a_password)
        {
            this->creation_settings.getCompetition().setPassword(a_password);
        });

        setPage(Page::Password, &password_page);
        return;
    }
    
    void CompetitionCreationWizard::createServerPage()
    {
        server_page.setTitle("Server " % pageNumber(Page::Server));
        server_page.setSubTitle("Specify a host for your competition");

        server_label.setWordWrap(true);
        server_label.setText(
            QString()
            % "Enter the address of the Division Result Server on which your competition will be hosted. "
            % "Depending on the host and network configuration, "
            % "it can be a local or public IP address, or even a domain. ");

        server_page.registerField("address*", &server_address_input);

        server_address_use_current_button.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        server_address_use_current_button.setIcon(QPixmap{":/icon/icons8-sync-96.png"});
        server_address_use_current_button.setToolTip("Use address from current configuration");

        server_address_use_last_button.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        server_address_use_last_button.setIcon(QPixmap{":/icon/icons8-history-96.png"});
        server_address_use_last_button.setToolTip("Use address from last competition creation");

        server_request_label.setWordWrap(true);
        server_request_label.setText(
            QString()
            % "Pressing \"Next\" will send a request to the server, "
            % "asking it to create your competition, "
            % "so the server must be live and reachable. ");

        int layout_row = 0;

        server_page_layout.addWidget(&server_label, layout_row++, 0);

        server_page_layout.setRowMinimumHeight(layout_row++, 10);

        server_address_layout.addWidget(&server_address_input, 0, 0);
        server_address_layout.addWidget(&server_address_use_last_button, 0, 1);
        server_address_layout.addWidget(&server_address_use_current_button, 0, 2);
        server_page_layout.addLayout(&server_address_layout, layout_row++, 0);

        server_page_layout.setRowMinimumHeight(layout_row++, 10);

        server_page_layout.addWidget(&server_request_label, layout_row++, 0);

        server_page.setLayout(&server_page_layout);

        connect(&server_address_input, &QLineEdit::textChanged, this, [this](const QString& a_address)
        {
            this->creation_settings.setWebserverAddress(a_address);
        });
        connect(&server_address_use_current_button, &QPushButton::clicked, this, [this]
        {
            this->server_address_input.setText(this->settings->getWebserverAddress());
        });
        connect(&server_address_use_last_button, &QPushButton::clicked, this, [this]
        {
            this->server_address_input.setText(this->last_creation_settings.getWebserverAddress());
        });

        setPage(Page::Server, &server_page);
        return;
    }
    
    void CompetitionCreationWizard::createResponsePage()
    {
        response_page.setTitle("Server Response " % pageNumber(Page::Response));
        response_page.setSubTitle("If all goes well, you won't be here for very long");

        setPage(Page::Response, &response_page);
        return;
    }
    
    void CompetitionCreationWizard::createSummaryPage()
    {
        summary_page.setTitle("Summary " % pageNumber(Page::Summary));
        summary_page.setSubTitle("That's it! Your competition has been created");

        summary_label.setWordWrap(true);
        summary_label.setText
        (
            QString()
            % "The server successfully created your competition with the data shown below. "
            % "If you leave the \"Use this competition now\" checkbox checked, "
            % "the competition ID, password and server address will be loaded into the main window "
            % "when you finish this wizard. "
            % "Alternatively, you can copy the data to your clipboard and save it elsewhere. "
        );

        summary_table.setModel(&summary_table_model);
        summary_table.horizontalHeader()->setVisible(false);
        summary_table.verticalHeader()->setVisible(false);
        summary_table.setSelectionMode(QAbstractItemView::NoSelection);
        summary_table.setEditTriggers(QAbstractItemView::NoEditTriggers);
        summary_table.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        summary_table.setFixedHeight(summary_table.verticalHeader()->length() + 2);

        summary_copy_button.setIcon(QPixmap{":/icon/icons8-copy-96.png"});
        summary_copy_button.setIconSize(QSize{24, 24});
        summary_copy_button.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        summary_copy_button.setStyleSheet("border: none; margin-top: 5px;");
        summary_copy_button.setCursor(Qt::PointingHandCursor);

        summary_use_now_checkbox.setText("Use this competition now");
        summary_use_now_checkbox.setToolTip("This will erase the current settings in the main window");

        summary_copy_label.setText("Copied to clipboard!");
        summary_copy_label.setVisible(false);

        summary_copy_label_timer.setSingleShot(true);

        int layout_row = 0;

        summary_page_layout.addWidget(&summary_label, layout_row++, 0);

        summary_page_layout.setRowMinimumHeight(layout_row++, 10);

        summary_page_layout.addWidget(&summary_table, layout_row, 0);
        summary_page_layout.addWidget(&summary_copy_button, layout_row++, 0, Qt::AlignRight | Qt::AlignTop);

        summary_page_layout.setRowMinimumHeight(layout_row++, 10);

        summary_checkbox_layout.addWidget(&summary_use_now_checkbox, 0, 0);
        summary_checkbox_layout.addWidget(&summary_copy_label, 0, 1, Qt::AlignRight);

        summary_page_layout.addLayout(&summary_checkbox_layout, layout_row++, 0);

        summary_page.setLayout(&summary_page_layout);

        connect(&summary_copy_button, &QPushButton::clicked, this, &CompetitionCreationWizard::copySummary);
        connect(&summary_copy_label_timer, &QTimer::timeout, [this]{ this->summary_copy_label.setVisible(false); });

        setPage(Page::Summary, &summary_page);
        return;
    }
    
    void CompetitionCreationWizard::populate()
    {
        if (first_launch)
        {
            creation_settings.setResultSource(settings->getResultSource());
            server_address_use_last_button.setVisible(false);
        }
        else
        {
            creation_settings = last_creation_settings;
            server_address_use_last_button.setVisible(true);
        }

        creation_settings.getCompetition().setPassword("");
        
        // Compatibility
        compatibility_page.populate();

        // Password
        password_input.setText(creation_settings.getCompetition().getPassword());

        // Server
        server_address_input.setText(creation_settings.getWebserverAddress());

        // Summary
        summary_use_now_checkbox.setChecked(true);

        return;
    }
    
    const QString CompetitionCreationWizard::pageNumber(Page a_page)
    {
        return QString() % "(" % QString::number(a_page + 1) % "/" % QString::number(Page::_Count) % ")";
    }
    
    void CompetitionCreationWizard::initiateRequest()
    {
        logger->clear();
        log(MessageType::Info, "Internal / Create New", 0, "Requesting...",
            "A request to create a new competition has been sent to the server");
                
        button(QWizard::BackButton)->setDisabled(true);
        emit requestNewCompetition(creation_settings);

        return;
    }
}