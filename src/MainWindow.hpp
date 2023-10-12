#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QDebug>

#include <array>
#include <limits>
#include <set>

#include <QAbstractItemView>
#include <QAction>
#include <QActionGroup>
#include <QCheckBox>
#include <QCloseEvent>
#include <QComboBox>
#include <QDate>
#include <QDateTimeEdit>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QFont>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QIcon>
#include <QItemSelectionModel>
#include <QKeySequence>
#include <QLabel>
#include <QLineEdit>
#include <QLocale>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QModelIndexList>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSizePolicy>
#include <QSpinBox>
#include <QString>
#include <QStringBuilder>
#include <QStringList>
#include <QTableView>
#include <QTextEdit>
#include <QThread>
#include <QTimer>
#include <QTimeZone>
#include <QVBoxLayout>
#include <QWidget>

#include "utils/ForwardDeclarations.hpp"

#include "AboutDialog.hpp"
#include "comp-create-wizard/CompetitionCreationWizard.hpp"
#include "ConfigValidator.hpp"
#include "Division.hpp"
#include "DivisionEditor.hpp"
#include "DivisionTableModel.hpp"
#include "utils/Helpers.hpp"
#include "logging/Loggable.hpp"
#include "logging/Logger.hpp"
#include "logging/LoggerProxy.hpp"
#include "workers/Coordinator.hpp"
#include "PersistentSettings.hpp"
#include "version/UpdateDialog.hpp"
#include "version/Version.hpp"
#include "version/VersionNotifier.hpp"

#include "utils/SignalDebouncer.hpp"

#include "EditorMode.hpp"
#include "logging/MessageType.hpp"

namespace divi
{
    class MainWindow : public QMainWindow, public Loggable
    {
        Q_OBJECT
        
        public:
            MainWindow(Version* a_version);
            ~MainWindow();
        
        signals:
            void updateResults(bool a_fresh_start);
            void deleteResults();

        private slots:
            void selectResultSource(ResultSource a_result_source);
            void start();
            void stop();
            void xmlResultFileChanged(const QString& a_file_path);
            int updateResultsIfAvailable(bool a_fresh_start = false);
            void setActivelyProcessing(bool a_state);
            void importConfig();
            void exportConfig();
            void browseWorkingDir();
            void browseDiviExe();
            void browseXmlResult();
            void updateInterfaceState();
            void editSelectedDivision();
            void deleteSelectedDivision();
            void updateCountdown();
            void loadNewCompetition(Settings& a_new_settings);
            void applyMetadataFromMeos(const Competition& a_competition);
            void deleteResultsPrompt();
        
        private:
            void closeEvent(QCloseEvent* a_event) override;

            void createHeader();
            void createCompetitionGroup();
            void createResultSourceGroup();
            void createDivisionsGroup();
            void createWebserverGroup();
            void createRunGroup();
            void createLogGroup();
            void populate();
            void initaliseMenus();
            void initialiseConnections();
            void disableRestrictedItems(bool a_disable);
            const QString getCompetitionUrl();
            void clearCompetitionAndDivision();
            void updateLiveresultsText();
            void setToolTips();
            void updateLayout();
            void startTimer();
            int startFileWatcher(const QString& a_file_path);

            bool running = false;
            bool actively_processing = false;
            bool waiting = false;

            Version* version;
            Logger* main_logger;
            Logger* file_logger;
            PersistentSettings settings;
            QThread worker;
            VersionNotifier version_notifier;
            Coordinator coordinator;
            QFileSystemWatcher file_watcher;

            QMenu competition_menu;
            QAction create_new_competition_action;
            CompetitionCreationWizard create_new_competition_wizard;
            QAction import_metadata_from_meos_action;
            QAction import_config_action;
            QAction export_config_action;
            QAction validate_config_action;
            ConfigValidator config_validator;

            QMenu compatibility_menu;
            QMenu result_source_menu;
            QActionGroup result_source_action_group;
            QAction meos_divi_source_action;
            QAction divi_source_action;
            QAction xml_divi_source_action;

            QMenu help_menu;
            QAction view_help;
            QAction view_about;
            AboutDialog about_dialog;
            QAction check_for_updates;
            UpdateDialog update_dialog;
            QAction open_github;
            QAction report_issue;

            QWidget central_widget;
            QGridLayout grid_layout;
            std::array<QVBoxLayout, 3> ui_columns;
            QWidget spacer;

            QLabel header{"Division Result Bridge"};
            QFont header_font;
            
            QFileDialog import_config_dialog;
            QFileDialog export_config_dialog;

            std::vector<QWidget*> restricted_inputs;
            std::vector<QAction*> restricted_actions;

            // Competition
            QGroupBox competition_group{"Competition"};
            QGridLayout competition_layout;

            QGridLayout competition_id_layout;
            QLabel competition_id_label{"Competition ID:"};
            QSpinBox competition_id_input;

            QGridLayout password_layout;
            QLabel password_label{"Password:"};
            QLineEdit password_input;
            QRegularExpression password_regex;
            QRegularExpressionValidator password_validator;
            QLabel password_text;

            QGridLayout competition_name_layout;
            QLabel competition_name_label{"Name:"};
            QLineEdit competition_name_input;

            QGridLayout organiser_layout;
            QLabel organiser_label{"Organiser:"};
            QLineEdit organiser_input;

            QGridLayout competition_date_layout;
            QLabel competition_date_label{"Date (YYYY-MM-DD):"};
            QDateTimeEdit competition_date_input;
            QWidget competition_date_spacer;
            QLabel competition_timezone_label{"Time zone:"};
            QComboBox competition_timezone_input;

            QGridLayout competition_visibility_layout;
            QLabel competition_visibility_label{"Visibility:"};
            QComboBox competition_visibility_input;
            QWidget competition_visibility_spacer;

            // Result source
            QGroupBox result_source_group{"Result Source"};
            QGridLayout result_source_layout;

            QGridLayout divi_exe_path_layout;
            QLabel divi_exe_path_label;
            QLineEdit divi_exe_path_input;
            QPushButton divi_exe_path_button{"..."};
            QFileDialog divi_exe_path_dialog;

            QWidget meos_address_container;
            QGridLayout meos_address_layout;
            QLabel meos_address_label{"MeOS information server address:"};
            QLineEdit meos_address_input;
            QPushButton meos_address_test_button{"Test"};

            QWidget xml_results_container;
            QGridLayout xml_results_layout;
            QLabel xml_results_label{"Path to IOF XML 3.0 result file:"};
            QLineEdit xml_results_input;
            QPushButton xml_results_path_button{"..."};
            QFileDialog xml_results_path_dialog;

            // Divisions
            QGroupBox divisions_group{"Divisions"};
            QGridLayout divisions_layout;
            QTableView division_table;
            DivisionTableModel division_table_model;
            DivisionEditor division_editor;

            QGridLayout division_button_layout;
            QPushButton new_division_button{"New"};
            QPushButton edit_division_button{"Edit"};
            QPushButton delete_division_button{"Delete"};
            QWidget left_division_button_spacer;
            QWidget right_division_button_spacer;

            QMessageBox delete_division_warning;
            QPushButton* delete_division_confirm_button;
            QPushButton* delete_division_cancel_button;

            // Web Server
            QGroupBox webserver_group{"Online"};
            QGridLayout webserver_layout;

            QGridLayout webserver_address_layout;
            QLabel webserver_address_label{"Division Result Server address:"};
            QLineEdit webserver_address_input;
            QPushButton webserver_ping_button{"Test"};

            QGridLayout webserver_manage_layout;
            QLabel webserver_manage_label{"Manage competition on server:"};
            QPushButton webserver_delete_results_button{"Delete Results"};
            QPushButton webserver_update_meta_button{"Update Metadata"};

            QGridLayout webserver_inspect_layout;
            QLabel webserver_inspect_label{"Inspect competition on server:"};
            QPushButton webserver_view_button{"View In Browser"};
            QPushButton webserver_analytics_button{"Fetch Analytics"};

            QGridLayout liveresults_layout;
            QLabel liveresults_label;
            QSpinBox liveresults_input;

            // Run
            QGroupBox run_group{"Update Results"};
            QGridLayout run_layout;
            QTimer run_timer;
            QTimer countdown_timer;
            SignalDebouncer<QString> xml_results_debouncer;

            QGridLayout working_dir_layout;
            QLabel working_dir_label{"Working directory:"};
            QLineEdit working_dir_input;
            QPushButton working_dir_button{"..."};
            QFileDialog working_dir_dialog;

            QGridLayout run_control_layout;
            QWidget run_control_spacer;

            QWidget update_interval_container;
            QGridLayout update_interval_layout;
            QLabel update_interval_label{"Update interval (seconds):"};
            QSpinBox update_interval_input;

            QGridLayout countdown_layout;
            QLabel countdown_label;
            QLabel countdown_time;

            QGridLayout run_buttons_layout;
            QPushButton start_button{"Start"};
            QPushButton stop_button{"Stop"};
            QPushButton run_once_button{"Run Once"};

            // Log
            QGroupBox log_group{"Log"};
            QGridLayout log_layout;
            QGridLayout save_logs_layout;
            QLabel save_logs_label{"Save logs:"};
            QWidget save_logs_spacer;
            QCheckBox save_pretty_log_input{"Pretty (HTML)"};
            QCheckBox save_raw_log_input{"Raw (plain text)"};
    };
}

#endif // __MAINWINDOW_H__