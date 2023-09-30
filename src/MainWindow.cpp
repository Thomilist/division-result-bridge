#include "MainWindow.hpp"


namespace divi
{
    MainWindow::MainWindow(Version* a_version)
        : version(a_version)
        , settings(this)
        , worker(this)
        , logger(new Logger(&settings, this))
        , version_notifier(logger, version, this)
        , coordinator(&settings, logger)
        , file_menu("Competition", this)
        , create_new_competition_action("Create new competition")
        , import_metadata_from_meos_action("Import metadata from MeOS")
        , import_config_action("Import configuration")
        , export_config_action("Export configuration")
        , config_validator(logger, &settings, this)
        , help_menu("Help", this)
        , view_help("View help", &help_menu)
        , view_about("About", &help_menu)
        , about_dialog(version, this)
        , check_for_updates("Check for updates", &help_menu)
        , update_dialog(version, this)
        , open_github("View source code", &help_menu)
        , report_issue("Report issue", &help_menu)
        , import_config_dialog(this, "Import configuration")
        , export_config_dialog(this, "Export configuration")
        , divi_exe_path_dialog(this, "Find " % Helpers::divisionsmatchberegningExeName())
        , division_table_model(&settings, this)
        , division_editor(&division_table_model, this)
        , create_competition_dialog(this)
        , competition_created_dialog(this)
        , run_timer(this)
        , countdown_timer(this)
    {
        setWindowIcon(QIcon{":/icon/icon.ico"});
        setMinimumWidth(1100);
        //setMinimumHeight(810);
        setMouseTracking(true);

        setLogger(logger);
        settings.setLogger(logger);
        
        import_config_dialog.setFileMode(QFileDialog::ExistingFile);
        import_config_dialog.setNameFilter("Config (*.json)");

        export_config_dialog.setFileMode(QFileDialog::AnyFile);
        export_config_dialog.setAcceptMode(QFileDialog::AcceptSave);
        export_config_dialog.setNameFilter("Config (*.json)");
        export_config_dialog.setDefaultSuffix("json");
        
        createHeader();
        createCompetitionGroup();
        createConfigGroup();
        createDivisionsGroup();
        createWebserverGroup();
        createRunGroup();
        createLogGroup();

        populate();
        initaliseMenus();
        initialiseConnections();

        spacer.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        
        grid_layout.addWidget(&header, 0, 0, 1, static_cast<int>(ui_columns.size()));

        ui_columns[0].addWidget(&competition_group);
        ui_columns[0].addWidget(&divisions_group);
        ui_columns[1].addWidget(&webserver_group);
        ui_columns[1].addWidget(&config_group);
        ui_columns[1].addWidget(&spacer);
        ui_columns[1].addWidget(&run_group);
        ui_columns[2].addWidget(&log_group);

        for (size_t index = 0; index < ui_columns.size(); ++index)
        {
            grid_layout.addLayout(&ui_columns[index], 1, static_cast<int>(index));
        }
        
        setCentralWidget(&central_widget);
        central_widget.setLayout(&grid_layout);

        coordinator.moveToThread(&worker);
        worker.start();

        config_validator.validate();

        setToolTips();
        updateInterfaceState();
        updateCountdown();
        show();
    }
    
    MainWindow::~MainWindow()
    {
        worker.quit();
        worker.wait();
    }
    
    void MainWindow::start()
    {
        if (running || actively_processing)
        {
            return;
        }

        running = true;
        updateInterfaceState();

        updateResultsIfAvailable(true);

        countdown_timer.start(200);
        run_timer.start(settings.getUpdateInterval() * 1000);
        
        updateCountdown();

        return;
    }
    
    void MainWindow::stop()
    {
        if (!running)
        {
            return;
        }

        countdown_timer.stop();
        run_timer.stop();
        
        running = false;
        disableRestrictedItems(false);
        updateInterfaceState();
        updateCountdown();

        return;
    }
    
    void MainWindow::updateResultsIfAvailable(bool a_fresh_start)
    {
        if (actively_processing)
        {
            log(MessageType::Warning, "Internal / Update Results", 0, "New Update Cancelled",
                "An update cannot be started while another one is running");
            return;
        }

        setActivelyProcessing(true);
        emit updateResults(a_fresh_start);
        return;
    }
    
    void MainWindow::setActivelyProcessing(bool a_state)
    {
        actively_processing = a_state;
        updateInterfaceState();
        return;
    }
    
    void MainWindow::importConfig()
    {
        if (import_config_dialog.exec())
        {
            QString file = import_config_dialog.selectedFiles().front();
            settings.importConfig(file);
            populate();
            import_config_dialog.setDirectory(QFileInfo{file}.absoluteDir());
            export_config_dialog.setDirectory(QFileInfo{file}.absoluteDir());
            config_validator.validate();
        }
        
        return;
    }
    
    void MainWindow::exportConfig()
    {
        if (export_config_dialog.exec())
        {
            QString file = export_config_dialog.selectedFiles().front();
            settings.exportConfig(file);
            import_config_dialog.setDirectory(QFileInfo{file}.absoluteDir());
            export_config_dialog.setDirectory(QFileInfo{file}.absoluteDir());
        }
        
        return;
    }
    
    void MainWindow::browseWorkingDir()
    {
        if (working_dir_dialog.exec())
        {
            QString directory = working_dir_dialog.directory().absolutePath();
            working_dir_input.setText(directory);
            working_dir_dialog.setDirectory(directory);
        }

        return;
    }
    
    void MainWindow::browseDiviExe()
    {
        if (divi_exe_path_dialog.exec())
        {
            QString file = divi_exe_path_dialog.selectedFiles().front();
            divi_exe_path_input.setText(file);
            divi_exe_path_dialog.setDirectory(QFileInfo{file}.absoluteDir());
        }

        return;
    }
    
    void MainWindow::updateInterfaceState()
    {
        bool competition_complete
            =  !competition_id_input.text().isEmpty()
            && competition_id_input.value() != 0
            && !password_input.text().isEmpty()
            && !organiser_input.text().isEmpty()
            && !competition_date_input.text().isEmpty()
            && !competition_name_input.text().isEmpty()
            && !competition_visibility_input.currentText().isEmpty();
        
        bool config_complete
            =  !working_dir_input.text().isEmpty()
            && !divi_exe_path_input.text().isEmpty()
            && !meos_address_input.text().isEmpty()
            && !webserver_address_input.text().isEmpty();
        
        bool webserver_defined
            =  !competition_id_input.text().isEmpty()
            && !webserver_address_input.text().isEmpty();
        
        bool meos_defined
            = !meos_address_input.text().isEmpty();
        
        bool divisions_empty = settings.getDivisions().size() == 0;
        bool division_selected = !division_table.selectionModel()->selectedIndexes().isEmpty();

        edit_division_button.setEnabled(!divisions_empty && division_selected);
        delete_division_button.setEnabled(!divisions_empty && division_selected);

        webserver_delete_results_button.setEnabled(webserver_defined && !running && !actively_processing);
        webserver_update_meta_button.setEnabled(webserver_defined && !running && !actively_processing);
        webserver_ping_button.setEnabled(webserver_defined && !running && !actively_processing);
        webserver_view_button.setEnabled(webserver_defined);
        
        import_metadata_from_meos_action.setEnabled(meos_defined);

        start_button.setEnabled(competition_complete && config_complete && !running && !actively_processing);
        run_once_button.setEnabled(competition_complete && config_complete && !running && !actively_processing);
        stop_button.setEnabled(running);

        if (running)
        {
            disableRestrictedItems(true);
        }

        division_table.resizeColumnsToContents();
        division_table.resizeRowsToContents();

        updateLiveresultsText();
        
        return;
    }
    
    void MainWindow::editSelectedDivision()
    {
        auto selection_model = division_table.selectionModel();
        QModelIndexList selected_indices = selection_model->selectedIndexes();

        if (selected_indices.isEmpty())
        {
            return;
        }

        Division division = settings.getDivisions().at(selected_indices.front().row());
        division_editor.launch(EditorMode::EditExisting, division);

        return;
    }
    
    void MainWindow::deleteSelectedDivision()
    {
        auto selection_model = division_table.selectionModel();
        QModelIndexList selected_indices = selection_model->selectedIndexes();

        if (selected_indices.isEmpty())
        {
            return;
        }

        Division division = settings.getDivisions().at(selected_indices.front().row());

        delete_division_warning.setText
        (
            QString()
            % "Are you sure you wish to delete the division \""
            % division.getName()
            % "\", ID "
            % QString::number(division.getID())
            % "?"
        );

        delete_division_warning.exec();

        if (delete_division_warning.clickedButton() == delete_division_confirm_button)
        {
            division_table_model.deleteDivision(division.getID());
        }

        return;
    }
    
    void MainWindow::updateCountdown()
    {
        if (!running)
        {
            countdown_time.setText("<i>N/A</i>");
        }
        else
        {
            int remaining = run_timer.remainingTime() / 1000;
            countdown_time.setText("<i>" % QString::number(remaining) % " s</i>");
        }

        return;
    }
    
    void MainWindow::loadNewCompetition(const Competition& a_competition)
    {
        clearCompetitionAndDivision();
        loadCompetitionMetadata(a_competition);
        return;
    }
    
    void MainWindow::applyMetadataFromMeos(const Competition& a_competition)
    {
        if (const QString name = a_competition.getName(); !name.isEmpty())
        {
            settings.getCompetition().setName(name);
        }

        if (const QString organiser = a_competition.getOrganiser(); !organiser.isEmpty())
        {
            settings.getCompetition().setOrganiser(organiser);
        }

        if (const QString date = a_competition.getDate(); !date.isEmpty())
        {
            settings.getCompetition().setDate(date);
        }

        populate();
        return;
    }
    
    void MainWindow::deleteResultsPrompt()
    {
        QMessageBox::StandardButton response = QMessageBox::No;

        response = QMessageBox::warning
        (
            this,
            "Delete results?",
            "Are you sure you wish to delete all results on the server for this competition?\nThis cannot be undone.",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No
        );

        if (response == QMessageBox::Yes)
        {
            emit deleteResults();
        }

        return;
    }
    
    void MainWindow::closeEvent(QCloseEvent* a_event)
    {
        if (running || actively_processing)
        {
            QMessageBox::StandardButton response = QMessageBox::No;

            response = QMessageBox::warning
            (
                this,
                "Close while running?",
                "Are you sure you wish to exit the program? Result updates are still running.",
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::No
            );

            if (response == QMessageBox::No)
            {
                a_event->ignore();
                return;
            }
        }

        QMainWindow::closeEvent(a_event);
        return;
    }
    
    void MainWindow::createHeader()
    {
        header_font.setPixelSize(30);
        header.setFont(header_font);
        header.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        return;
    }
    
    void MainWindow::createCompetitionGroup()
    {
        restricted_inputs.push_back(&competition_id_input);
        restricted_inputs.push_back(&password_input);
        restricted_inputs.push_back(&competition_name_input);
        restricted_inputs.push_back(&organiser_input);
        restricted_inputs.push_back(&competition_date_input);
        restricted_inputs.push_back(&competition_visibility_input);
        
        competition_id_input.setMinimum(0);
        competition_id_input.setMaximum(std::numeric_limits<int>::max());

        password_regex.setPattern(Helpers::passwordRegex());
        password_validator.setRegularExpression(password_regex);
        password_input.setValidator(&password_validator);

        password_text.setTextFormat(Qt::RichText);
        password_text.setWordWrap(true);
        password_text.setText
        (
            Helpers::passwordDisclaimer()
        );

        competition_date_input.setDisplayFormat(Helpers::dateFormat());
        competition_date_input.setCalendarPopup(true);
        competition_date_input.setMaximumWidth(competition_date_label.sizeHint().width());

        competition_visibility_input.addItems
        ({
            Helpers::visibility(Visibility::PUBLIC),
            Helpers::visibility(Visibility::HIDDEN),
            Helpers::visibility(Visibility::PRIVATE)
        });
        
        int row = 0;

        competition_id_layout.addWidget(&competition_id_label, 0, 0);
        competition_id_layout.addWidget(&competition_id_input, 1, 0);
        competition_layout.addLayout(&competition_id_layout, row++, 0);

        competition_layout.setRowMinimumHeight(row++, Helpers::verticalPadding());

        password_layout.addWidget(&password_label, 0, 0);
        password_layout.addWidget(&password_input, 1, 0);
        password_layout.addWidget(&password_text, 2, 0);
        competition_layout.addLayout(&password_layout, row++, 0);

        competition_layout.setRowMinimumHeight(row++, Helpers::verticalPadding());

        competition_name_layout.addWidget(&competition_name_label, 0, 0);
        competition_name_layout.addWidget(&competition_name_input, 1, 0);
        competition_layout.addLayout(&competition_name_layout, row++, 0);

        competition_layout.setRowMinimumHeight(row++, Helpers::verticalPadding());

        organiser_layout.addWidget(&organiser_label, 0, 0);
        organiser_layout.addWidget(&organiser_input, 1, 0);
        competition_layout.addLayout(&organiser_layout, row++, 0);

        competition_layout.setRowMinimumHeight(row++, Helpers::verticalPadding());

        competition_date_layout.addWidget(&competition_date_label, 0, 0);
        competition_date_layout.addWidget(&competition_date_input, 1, 0);
        //competition_date_spacer.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        competition_date_layout.addWidget(&competition_date_spacer, 1, 1);
        competition_date_layout.addWidget(&competition_visibility_label, 0, 2);
        competition_date_layout.addWidget(&competition_visibility_input, 1, 2);
        competition_layout.addLayout(&competition_date_layout, row++, 0);

        competition_spacer.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        //competition_layout.addWidget(&competition_spacer, row++, 0);
        
        competition_group.setLayout(&competition_layout);
        competition_group.setAlignment(Qt::AlignHCenter);

        return;
    }
    
    void MainWindow::createConfigGroup()
    {
        restricted_inputs.push_back(&working_dir_input);
        restricted_inputs.push_back(&working_dir_button);
        restricted_inputs.push_back(&divi_exe_path_input);
        restricted_inputs.push_back(&divi_exe_path_button);
        restricted_inputs.push_back(&meos_address_input);
        restricted_inputs.push_back(&meos_address_test_button);
        
        working_dir_input.setReadOnly(true);
        working_dir_button.setMaximumWidth(25);

        working_dir_dialog.setFileMode(QFileDialog::Directory);
        
        divi_exe_path_input.setReadOnly(true);
        divi_exe_path_button.setMaximumWidth(25);

        divi_exe_path_dialog.setFileMode(QFileDialog::ExistingFile);
        divi_exe_path_dialog.setNameFilter("Program (*.exe)");

        divi_exe_path_label.setText
        (
            QString()
            % "Path to "
            % Helpers::divisionsmatchberegningExeName()
            % ":"
        );
        
        int row = 0;

        working_dir_layout.addWidget(&working_dir_label, 0, 0);
        working_dir_layout.addWidget(&working_dir_input, 1, 0);
        working_dir_layout.addWidget(&working_dir_button, 1, 1);
        config_layout.addLayout(&working_dir_layout, row++, 0);

        config_layout.setRowMinimumHeight(row++, Helpers::verticalPadding());

        divi_exe_path_layout.addWidget(&divi_exe_path_label, 0, 0);
        divi_exe_path_layout.addWidget(&divi_exe_path_input, 1, 0);
        divi_exe_path_layout.addWidget(&divi_exe_path_button, 1, 1);
        config_layout.addLayout(&divi_exe_path_layout, row++, 0);

        config_layout.setRowMinimumHeight(row++, Helpers::verticalPadding());

        meos_address_test_button.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

        meos_address_layout.addWidget(&meos_address_label, 0, 0);
        meos_address_layout.addWidget(&meos_address_input, 1, 0);
        meos_address_layout.addWidget(&meos_address_test_button, 1, 1);
        config_layout.addLayout(&meos_address_layout, row++, 0);

        config_group.setLayout(&config_layout);
        config_group.setAlignment(Qt::AlignHCenter);

        return;
    }
    
    void MainWindow::createDivisionsGroup()
    {
        restricted_inputs.push_back(&division_table);
        restricted_inputs.push_back(&new_division_button);
        restricted_inputs.push_back(&edit_division_button);
        restricted_inputs.push_back(&delete_division_button);

        division_table.setModel(&division_table_model);
        division_table.setSelectionBehavior(QAbstractItemView::SelectRows);
        division_table.setSelectionMode(QAbstractItemView::SingleSelection);
        division_table.setEditTriggers(QAbstractItemView::NoEditTriggers);
        division_table.horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        division_table.verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        //division_table.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        division_table.setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        division_table.setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        division_table.setAutoScroll(false);

        delete_division_warning.setWindowTitle("Overwrite Division");
        delete_division_warning.setIcon(QMessageBox::Warning);

        delete_division_confirm_button = delete_division_warning.addButton("Delete", QMessageBox::AcceptRole);
        delete_division_cancel_button = delete_division_warning.addButton("Cancel", QMessageBox::RejectRole);
        
        int row = 0;

        divisions_layout.addWidget(&division_table, row++, 0);

        int column = 0;

        division_button_layout.addWidget(&left_division_button_spacer, 0, column++);
        division_button_layout.addWidget(&new_division_button, 0, column++);
        division_button_layout.addWidget(&edit_division_button, 0, column++);
        division_button_layout.addWidget(&delete_division_button, 0, column++);
        division_button_layout.addWidget(&right_division_button_spacer, 0, column++);
        divisions_layout.addLayout(&division_button_layout, row++, 0);

        divisions_group.setLayout(&divisions_layout);
        divisions_group.setAlignment(Qt::AlignHCenter);

        return;
    }
    
    void MainWindow::createWebserverGroup()
    {
        restricted_inputs.push_back(&webserver_address_input);
        restricted_inputs.push_back(&webserver_ping_button);
        restricted_inputs.push_back(&webserver_delete_results_button);
        restricted_inputs.push_back(&webserver_update_meta_button);
        restricted_inputs.push_back(&webserver_analytics_button);
        restricted_inputs.push_back(&liveresults_input);

        liveresults_label.setTextFormat(Qt::RichText);
        liveresults_label.setTextInteractionFlags(Qt::TextBrowserInteraction);
        liveresults_label.setOpenExternalLinks(true);
        updateLiveresultsText();
        
        liveresults_input.setMinimum(0);
        liveresults_input.setMaximum(std::numeric_limits<int>::max());
        
        int row = 0;

        webserver_ping_button.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

        webserver_address_layout.addWidget(&webserver_address_label, 0, 0);
        webserver_address_layout.addWidget(&webserver_address_input, 1, 0);
        webserver_address_layout.addWidget(&webserver_ping_button, 1, 1);
        webserver_layout.addLayout(&webserver_address_layout, row++, 0);

        webserver_layout.setRowMinimumHeight(row++, Helpers::verticalPadding());

        webserver_manage_layout.addWidget(&webserver_manage_label, 0, 0);
        webserver_manage_layout.addWidget(&webserver_delete_results_button, 1, 0);
        webserver_manage_layout.addWidget(&webserver_update_meta_button, 1, 1);
        webserver_layout.addLayout(&webserver_manage_layout, row++, 0);

        webserver_layout.setRowMinimumHeight(row++, Helpers::verticalPadding());
        
        webserver_inspect_layout.addWidget(&webserver_inspect_label, 0, 0);
        webserver_inspect_layout.addWidget(&webserver_view_button, 1, 0);
        webserver_inspect_layout.addWidget(&webserver_analytics_button, 1, 1);
        webserver_layout.addLayout(&webserver_inspect_layout, row++, 0);

        webserver_layout.setRowMinimumHeight(row++, Helpers::verticalPadding());

        liveresults_layout.addWidget(&liveresults_label, 0, 0);
        liveresults_layout.addWidget(&liveresults_input, 1, 0);
        webserver_layout.addLayout(&liveresults_layout, row++, 0);

        webserver_group.setLayout(&webserver_layout);
        webserver_group.setAlignment(Qt::AlignHCenter);

        return;
    }
    
    void MainWindow::createRunGroup()
    {
        restricted_inputs.push_back(&update_interval_input);
        
        update_interval_input.setMinimum(10);
        update_interval_input.setMaximum(3600);
        update_interval_input.setMaximumWidth(update_interval_label.sizeHint().width());

        countdown_label.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        countdown_time.setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        countdown_label.setTextFormat(Qt::RichText);
        countdown_time.setTextFormat(Qt::RichText);

        countdown_label.setText("<i>Next update:</i>");

        int row = 0;

        int column = 0;

        update_interval_layout.addWidget(&update_interval_label, 0, 0);
        update_interval_layout.addWidget(&update_interval_input, 1, 0);

        countdown_layout.addWidget(&countdown_label, 0, 0);
        countdown_layout.addWidget(&countdown_time, 0, 1);
        update_interval_layout.addLayout(&countdown_layout, 2, 0);

        run_layout.addLayout(&update_interval_layout, row, column++);

        run_layout.addWidget(&run_spacer, row, column++);
        
        int button_row = 0;

        for (auto button : {&start_button, &stop_button, &run_once_button})
        {
            run_buttons_layout.addWidget(button, button_row++, 0);
        }

        run_layout.addLayout(&run_buttons_layout, row, column++);

        run_group.setLayout(&run_layout);
        run_group.setAlignment(Qt::AlignHCenter);

        return;
    }
    
    void MainWindow::createLogGroup()
    {
        logger->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        logger->setMinimumWidth(300);

        save_logs_spacer.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        int column = 0;

        save_logs_layout.addWidget(&save_logs_label, 0, column++);
        save_logs_layout.addWidget(&save_logs_spacer, 0, column++);
        save_logs_layout.addWidget(&save_pretty_log_input, 0, column++);
        save_logs_layout.addWidget(&save_raw_log_input, 0, column++);

        int row = 0;

        log_layout.addLayout(&save_logs_layout, row++, 0);
        log_layout.addWidget(logger, row++, 0);
        log_group.setLayout(&log_layout);
        log_group.setAlignment(Qt::AlignHCenter);

        log_group.setMouseTracking(true);

        return;
    }
    
    void MainWindow::populate()
    {
        // Competition
        competition_id_input.setValue(settings.getCompetition().getID());
        password_input.setText(settings.getCompetition().getPassword());
        competition_name_input.setText(settings.getCompetition().getName());
        organiser_input.setText(settings.getCompetition().getOrganiser());
        competition_visibility_input.setCurrentText(settings.getCompetition().getVisibility());

        if (settings.getCompetition().getDate().isEmpty())
        {
            competition_date_input.setDate(QDate::currentDate());
        }
        else
        {
            competition_date_input.setDate(QDate::fromString(settings.getCompetition().getDate(), Qt::ISODate));
        }

        // Configuration
        working_dir_input.setText(settings.getWorkingDir());
        divi_exe_path_input.setText(settings.getDiviExePath());
        meos_address_input.setText(settings.getMeosAddress());

        // Web server
        webserver_address_input.setText(settings.getWebserverAddress());
        liveresults_input.setValue(settings.getCompetition().getLiveresultsID());

        // Run
        update_interval_input.setValue(settings.getUpdateInterval());

        // Log
        save_pretty_log_input.setChecked(settings.getPrettyLogging());
        save_raw_log_input.setChecked(settings.getRawLogging());

        return;
    }
    
    void MainWindow::initaliseMenus()
    {
        restricted_actions.push_back(&create_new_competition_action);
        restricted_actions.push_back(&import_metadata_from_meos_action);
        restricted_actions.push_back(&import_config_action);
        restricted_actions.push_back(&export_config_action);
        
        menuBar()->addMenu(&file_menu);
        file_menu.addAction(&create_new_competition_action);
        file_menu.addSeparator();
        file_menu.addAction(&import_metadata_from_meos_action);
        file_menu.addSeparator();
        file_menu.addAction(&import_config_action);
        file_menu.addAction(&export_config_action);
        
        menuBar()->addMenu(&help_menu);
        help_menu.addAction(&view_help);
        help_menu.addAction(&view_about);
        help_menu.addAction(&check_for_updates);
        help_menu.addAction(&open_github);
        help_menu.addAction(&report_issue);

        view_help.setShortcut(QKeySequence{"F1"});
    }
    
    void MainWindow::initialiseConnections()
    {
        // File menu
        connect(&create_new_competition_action, &QAction::triggered, &create_competition_dialog, &CreateCompetitionDialog::open);
        connect(&import_metadata_from_meos_action, &QAction::triggered, &coordinator, &Coordinator::fetchMetadataFromMeos);
        connect(&coordinator, &Coordinator::metadataFetched, this, &MainWindow::applyMetadataFromMeos);
        connect(&import_config_action, &QAction::triggered, this, &MainWindow::importConfig);
        connect(&export_config_action, &QAction::triggered, this, &MainWindow::exportConfig);

        // Help menu
        connect(&view_help, &QAction::triggered, []{ QDesktopServices::openUrl(QUrl{Helpers::gitHubWikiUrl(), QUrl::TolerantMode}); });
        connect(&view_about, &QAction::triggered, &about_dialog, &AboutDialog::open);
        connect(&check_for_updates, &QAction::triggered, &update_dialog, &UpdateDialog::manualUpdateCheck);
        connect(&open_github, &QAction::triggered, []{ QDesktopServices::openUrl(QUrl{Helpers::gitHubRepoUrl(), QUrl::TolerantMode}); });
        connect(&report_issue, &QAction::triggered, []{ QDesktopServices::openUrl(QUrl{Helpers::gitHubIssuesUrl(), QUrl::TolerantMode}); });

        // Path navigation buttons
        connect(&working_dir_button, &QPushButton::clicked, this, &MainWindow::browseWorkingDir);
        connect(&divi_exe_path_button, &QPushButton::clicked, this, &MainWindow::browseDiviExe);

        // Divisions
        connect(&division_table_model, &DivisionTableModel::dataChanged, this, &MainWindow::updateInterfaceState);
        connect(&division_table, &QAbstractItemView::pressed, this, &MainWindow::updateInterfaceState);
        connect(&new_division_button, &QPushButton::clicked, this, [this]{ this->division_editor.launch(EditorMode::CreateNew, Division()); });
        connect(&edit_division_button, &QPushButton::clicked, this, &MainWindow::editSelectedDivision);
        connect(&delete_division_button, &QPushButton::clicked, this, &MainWindow::deleteSelectedDivision);
        connect(&settings, &PersistentSettings::clearDivisions, &division_table_model, &DivisionTableModel::clear);
        connect(&settings, &PersistentSettings::addDivision, &division_table_model, &DivisionTableModel::addOrOverwriteDivision);

        // Create competition
        connect(&create_competition_dialog, &CreateCompetitionDialog::createCompetition, &coordinator, &Coordinator::createCompetition);
        connect(&coordinator, &Coordinator::competitionCreated, &competition_created_dialog, &CompetitionCreatedDialog::open);
        connect(&competition_created_dialog, &CompetitionCreatedDialog::useCompetitionNow, this, &MainWindow::loadNewCompetition);
        
        // Web server
        connect(&webserver_delete_results_button, &QPushButton::clicked, this, &MainWindow::deleteResultsPrompt);
        connect(this, &MainWindow::deleteResults, &coordinator, &Coordinator::deleteResults);
        connect(&webserver_update_meta_button, &QPushButton::clicked, &coordinator, &Coordinator::updateMetadata);

        connect(&webserver_view_button, &QPushButton::clicked, this, [this]{ QDesktopServices::openUrl(QUrl{this->getCompetitionUrl(), QUrl::TolerantMode}); });
        connect(&webserver_analytics_button, &QPushButton::clicked, &coordinator, &Coordinator::fetchAnalytics);
        connect(&webserver_ping_button, &QPushButton::clicked, &coordinator, &Coordinator::pingWebserver);

        // Configuration
        connect(&meos_address_test_button, &QPushButton::clicked, &coordinator, &Coordinator::pingMeos);

        // Update results
        connect(&start_button, &QPushButton::clicked, this, &MainWindow::start);
        connect(&stop_button, &QPushButton::clicked, this, &MainWindow::stop);
        connect(&run_once_button, &QPushButton::clicked, this, [this]{ this->updateResultsIfAvailable(true); });
        connect(&run_timer, &QTimer::timeout, this, [this]{ this->updateResultsIfAvailable(false); });
        connect(&countdown_timer, &QTimer::timeout, this, &MainWindow::updateCountdown);
        connect(&coordinator, &Coordinator::activelyProcessing, this, &MainWindow::setActivelyProcessing);
        connect(this, &MainWindow::updateResults, &coordinator, &Coordinator::updateResults);

        // Inputs, competition
        connect(&competition_id_input, &QSpinBox::valueChanged, this, [this](int a_id)
        {
            this->settings.getCompetition().setID(a_id);
            this->updateInterfaceState();
        });
        connect(&password_input, &QLineEdit::textChanged, this, [this](const QString& a_text)
        {
            this->settings.getCompetition().setPassword(a_text);
            this->updateInterfaceState();
        });
        connect(&competition_name_input, &QLineEdit::textChanged, this, [this](const QString& a_text)
        {
            this->settings.getCompetition().setName(a_text);
            this->updateInterfaceState();
        });
        connect(&organiser_input, &QLineEdit::textChanged, this, [this](const QString& a_text)
        {
            this->settings.getCompetition().setOrganiser(a_text);
            this->updateInterfaceState();
        });
        connect(&competition_date_input, &QDateTimeEdit::dateChanged, this, [this](const QDate& a_date)
        {
            this->settings.getCompetition().setDate(a_date);
            this->updateInterfaceState();
        });
        connect(&competition_visibility_input, &QComboBox::currentTextChanged, this, [this](const QString& a_visibility)
        {
            this->settings.getCompetition().setVisibility(a_visibility);
            this->updateInterfaceState();
        });

        // Inputs, configuration
        connect(&working_dir_input, &QLineEdit::textChanged, this, [this](const QString& a_text)
        {
            this->settings.setWorkingDir(a_text);
            this->updateInterfaceState();
        });
        connect(&divi_exe_path_input, &QLineEdit::textChanged, this, [this](const QString& a_text)
        {
            this->settings.setDiviExePath(a_text);
            this->updateInterfaceState();
        });
        connect(&meos_address_input, &QLineEdit::textChanged, this, [this](const QString& a_text)
        {
            this->settings.setMeosAddress(a_text);
            this->updateInterfaceState();
        });

        // Inputs, web server
        connect(&webserver_address_input, &QLineEdit::textChanged, this, [this](const QString& a_text)
        {
            this->settings.setWebserverAddress(a_text);
            this->updateInterfaceState();
        });
        connect(&liveresults_input, &QSpinBox::valueChanged, this, [this](int a_id)
        {
            this->settings.getCompetition().setLiveresultsID(a_id);
            this->updateInterfaceState();
        });

        // Inputs, run
        connect(&update_interval_input, &QSpinBox::valueChanged, this, [this](int a_interval)
        {
            this->settings.setUpdateInterval(a_interval);
            this->updateInterfaceState();
        });

        // Inputs, log
        connect(&save_pretty_log_input, &QCheckBox::stateChanged, this, [this](bool a_state)
        {
            this->settings.setPrettyLogging(a_state);
            this->updateInterfaceState();
        });
        connect(&save_raw_log_input, &QCheckBox::stateChanged, this, [this](bool a_state)
        {
            this->settings.setRawLogging(a_state);
            this->updateInterfaceState();
        });

        return;
    }
    
    void MainWindow::disableRestrictedItems(bool a_disable)
    {
        for (auto input : restricted_inputs)
        {
            input->setDisabled(a_disable);
        }

        for (auto action : restricted_actions)
        {
            action->setDisabled(a_disable);
        }

        return;
    }
    
    const QString MainWindow::getCompetitionUrl()
    {
        QString url = settings.getWebserverAddress();
        
        if (url.isEmpty())
        {
            return QString();
        }

        return Helpers::addressEndingWithSlash(url) % "competition/" % QString::number(settings.getCompetition().getID());
    }
    
    void MainWindow::clearCompetitionAndDivision()
    {
        settings.getCompetition().setID(0);
        settings.getCompetition().setPassword("");
        settings.getCompetition().setName("");
        settings.getCompetition().setOrganiser("");
        settings.getCompetition().setVisibility(Helpers::visibility(Visibility::PRIVATE));
        settings.getCompetition().setDate(QDate::currentDate());
        settings.getCompetition().setLiveresultsID(0);

        division_table_model.clear();

        populate();
        return;
    }
    
    void MainWindow::loadCompetitionMetadata(const Competition& a_competition)
    {
        settings.getCompetition() = a_competition;
        populate();
        return;
    }
    
    void MainWindow::updateLiveresultsText()
    {
        QString liveresults_url;

        if (settings.getCompetition().getLiveresultsID() > 0)
        {
            liveresults_url =
                QString()
                % "https://liveresultat.orientering.se/followfull.php?comp="
                % QString::number(settings.getCompetition().getLiveresultsID())
                % "&lang=en";
        }
        else
        {
            liveresults_url = "https://liveresultat.orientering.se/index.php?lang=en";
        }
        
        liveresults_label.setText
        (
            QString()
            % "Competition ID for "
            % "<a href=\""
            % liveresults_url
            % "\">"
            % "liveresultat.orientering.se"
            % "</a>"
            % " (optional):"
        );

        return;
    }
    
    void MainWindow::setToolTips()
    {
        // Competition menu
        create_new_competition_action.setToolTip(
            "Create a new competition on the web server, thereby obtaining a competition ID");
        import_metadata_from_meos_action.setToolTip(
            "Import the competition name, organiser and date from MeOS's information server");
        import_config_action.setToolTip(
            "Import a competition configuration from a file");
        export_config_action.setToolTip(
            "Export the current competition configuration to a file");

        // Help menu
        view_help.setToolTip(
            "Open the project's online documentation on GitHub, available in both Danish and English");
        view_about.setToolTip(
            "Show information about the program and its author, including contact info");
        check_for_updates.setToolTip(
            "Check if a new version has been released");
        open_github.setToolTip(
            "Open the project's source code repository on GitHub");
        report_issue.setToolTip(
            "Report an issue or suggest a feature or improvement on the project's issue tracker on GitHub");

        // Competition
        competition_id_input.setToolTip(
            "This is given to you when you create a new competition under the Competition menu");
        password_input.setToolTip(
            "Not secure. Needed for most interactions with your competition on the server");
        competition_name_input.setToolTip(
            "The name of the whole competition");
        organiser_input.setToolTip(
            "The name of the organiser of the competition");
        competition_date_input.setToolTip(
            "The date when the competition takes place");
        competition_visibility_input.setToolTip(
            "The competition's visibility level on the website");

        // Divisions
        new_division_button.setToolTip(
            "Configure a new division and add it to the competition");
        edit_division_button.setToolTip(
            "Click on a division in the list, then use this button to edit its configuration");
        delete_division_button.setToolTip(
            "Click on a division in the list, then use this button to remove it from the competition");

        // Web server
        webserver_address_input.setToolTip(
            "The network address of the web server that hosts your competition and presents it to end users");
        webserver_analytics_button.setToolTip(
            "Fetch the current competition's analytics from the server, containing data such as page visits");
        webserver_delete_results_button.setToolTip(
            "Delete all results associated with this competition on the web server");
        webserver_view_button.setToolTip(
            "View the current competition in the browser");
        webserver_ping_button.setToolTip(
            "Check the status of the web server and, if available, the status of the current competition on the web server");
        webserver_update_meta_button.setToolTip(
            "Update the current competition's name, organiser, date, visibility, division IDs and names, and liveresultat.orientering.se ID on the web server");
        liveresults_input.setToolTip(
            "This number is given to you when you create your competition on their site");

        // Local configuration
        working_dir_input.setToolTip(
            "Specify where temporary files and logs should be placed");
        working_dir_button.setToolTip(
            "Find with file browser...");
        divi_exe_path_input.setToolTip(
            "Point to your installation of Divisionsmatchberegning");
        divi_exe_path_button.setToolTip(
            "Find with file browser...");
        meos_address_input.setToolTip(
            "The network address of MeOS's information server. Make sure the service is running");
        meos_address_test_button.setToolTip(
            "Check if MeOS's information server is reachable on the provided address");

        // Update results
        update_interval_input.setToolTip(
            "Specify how frequently to check for new results and, if found, upload them to the web server");
        start_button.setToolTip(
            "Start the update timer, also triggering an update immediately");
        stop_button.setToolTip(
            "Stop the update timer. Ongoing updates are not interrupted");
        run_once_button.setToolTip(
            "Trigger one update immediately");

        // Log
        save_logs_label.setToolTip(
            "Logs are saved to files in the working directory");
        save_pretty_log_input.setToolTip(
            "Same content and formatting as seen in the log panel. For viewing in a browser");
        save_raw_log_input.setToolTip(
            "Same content as seen in the log panel, but no formatting. For viewing in a plain text editor or terminal");

        return;
    }
}