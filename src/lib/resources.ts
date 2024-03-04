export const resources =
{
    internal:
    {
        home:
        {
            label: "project.name",
            route: "/"
        },
        download:
        {
            label: "page.download.title",
            route: "/download"
        },
        docs:
        {
            label: "page.docs.title",
            route: "/docs/preface/introduction",
            collection:
            {
                preface:
                {
                    page:
                    {
                        route:
                        {
                            introduction: "/docs/getting-started/introduction"
                        }
                    }
                },
                getting_started:
                {
                    page:
                    {
                        route:
                        {
                            prerequisites: "/docs/getting-started/prerequisites",
                            installation: "/docs/getting-started/installation"
                        }
                    }
                }
            }
        },
        privacy:
        {
            label: "page.privacy.title",
            route: "/privacy"
        },
        license:
        {
            label: "page.license.title",
            route: "/license"
        },
        about:
        {
            label: "page.about.title",
            route: "/about"
        }
    },
    external:
    {
        andersklinting:
        {
            name: "Anders Klinting",
            handle: "AndersKlinting",
            project:
            {
                divisionsmatchberegning:
                {
                    name: "Divisionsmatchberegning",
                    exe_name: "Divisionsmatch.exe",
                    route:
                    {
                        repo: "https://github.com/AndersKlinting/divisionsmatchberegning",
                        download: "https://www.orientering.dk/divisionsmatch/"
                    }
                }
            }
        },
        bootstrap:
        {
            name: "Bootstrap",
            handle: "twbs",
            project:
            {
                icons:
                {
                    name: "Bootstrap Icons",
                    route:
                    {
                        repo: "https://github.com/twbs/icons",
                        website: "https://icons.getbootstrap.com/"
                    }
                }
            }
        },
        iof:
        {
            name: "International Orienteering Federation",
            short_name: "IOF",
            project:
            {
                iof_xml_3:
                {
                    name: "IOF XML 3.0"
                }
            }
        },
        liveresults:
        {
            name: "LiveResults",
            handle: "liveresults",
            project:
            {
                liveresults:
                {
                    name: "LiveResults",
                    route:
                    {
                        repo: "https://github.com/liveresults/documentation",
                        website: "https://liveresultat.orientering.se/index.php?lang=en"
                    }
                }
            }
        },
        microsoft:
        {
            name: "Microsoft",
            project:
            {
                windows:
                {
                    name: "Windows"
                },
                windows10:
                {
                    name: "Windows 10"
                }
            }
        },
        melinsoftware:
        {
            name: "Melin Software",
            handle: "melinsoftware",
            project:
            {
                meos:
                {
                    name: "MeOS",
                    route:
                    {
                        website: "https://www.melin.nu/meos/en/",
                        repo: "https://github.com/melinsoftware/meos",
                        info_server: "https://www.melin.nu/meos/en/show.php?base=4200&id=4242"
                    },
                    version:
                    {
                        infoserver: "3.5"
                    }
                }
            }
        },
        mozilla:
        {
            name: "Mozilla",
            route:
            {
                website: "https://www.mozilla.org/"
            },
            project:
            {
                mdn:
                {
                    name: "MDN Web Docs",
                    route:
                    {
                        repo: "https://github.com/mdn",
                        website: "https://developer.mozilla.org/",
                        web_storage_api: "https://developer.mozilla.org/docs/Web/API/Web_Storage_API"
                    }
                }
            }
        },
        qt:
        {
            name: "Qt Group",
            route:
            {
                website: "https://www.qt.io/"
            },
            project:
            {
                qt6:
                {
                    name: "Qt 6",
                    route:
                    {
                        website: "https://www.qt.io/product/qt6",
                        docs: "https://doc.qt.io/qt-6/",
                        qsettings: "https://doc.qt.io/qt-6/qsettings.html#details"
                    }
                }
            }
        },
        semver:
        {
            route:
            {
                website: "https://semver.org/",
                repo: "https://github.com/semver/semver"
            }
        },
        thomilist:
        {
            name: "Thomas Emil Jensen",
            handle: "Thomilist",
            project:
            {
                division_result_bridge:
                {
                    name: "Division Result Bridge",
                    exe_name: "division-result-bridge.exe",
                    route:
                    {
                        repo: "https://github.com/Thomilist/division-result-bridge",
                        license: "https://raw.githubusercontent.com/Thomilist/division-result-bridge/main/LICENSE",
                        releases: "https://github.com/Thomilist/division-result-bridge/releases"
                    },
                    interface:
                    {
                        example:
                        {
                            password: "hunter2",
                            server_address: "http://localhost:5174/"
                        },
                        menu_bar:
                        {
                            competition:
                            {
                                label: "Competition",
                                item:
                                {
                                    create_new:
                                    {
                                        label: "Create new competition"
                                    },
                                    import:
                                    {
                                        label: "Import"
                                    },
                                    export:
                                    {
                                        label: "Export"
                                    },
                                    validate:
                                    {
                                        label: "Validate"
                                    }
                                }
                            },
                            compatibility:
                            {
                                label: "Compatibility",
                                item:
                                {
                                    result_source:
                                    {
                                        label: "Result Source",
                                        item:
                                        {
                                            meos_divi:
                                            {
                                                label: "MeOS + Divisionsmatchberegning"
                                            },
                                            divi:
                                            {
                                                label: "Divisionsmatchberegning"
                                            },
                                            xml_divi:
                                            {
                                                label: "IOF XML file + Divisionsmatchberegning"
                                            }
                                        }
                                    }
                                }
                            },
                            help:
                            {
                                label: "Help"
                            }
                        },
                        comp_wizard:
                        {
                            button:
                            {
                                help:
                                {
                                    label: "Help"
                                },
                                back:
                                {
                                    label: "Back"
                                },
                                next:
                                {
                                    label: "Next"
                                },
                                cancel:
                                {
                                    label: "Cancel"
                                },
                                finish:
                                {
                                    label: "Finish"
                                },
                            },
                            page:
                            {
                                introduction:
                                {
                                    title: "Introduction"
                                },
                                compatibility:
                                {
                                    title: "Compatibility",
                                    meos_divi: "MeOS + Divisionsmatchberegning",
                                    divi: "Divisionsmatchberegning",
                                    xml_divi: "IOF XML 3.0 file + Divisionsmatchberegning"
                                },
                                password:
                                {
                                    title: "Password"
                                },
                                server:
                                {
                                    title: "Server"
                                },
                                response:
                                {
                                    title: "Server Response"
                                },
                                summary:
                                {
                                    title: "Summary",
                                    use_now: "Use this competition now"
                                },
                            }
                        },
                        main:
                        {
                            pane:
                            {
                                competition:
                                {
                                    header: "Competition"
                                },
                                divisions:
                                {
                                    header: "Divisions"
                                },
                                online:
                                {
                                    header: "Online"
                                },
                                result_source:
                                {
                                    header: "Result Source",
                                    item:
                                    {
                                        divi_exe_path:
                                        {
                                            labels:
                                            {
                                                field: "Path to Divisionsmatch.exe",
                                                path_button: "..."
                                            }
                                        },
                                        meos_server_address:
                                        {
                                            labels:
                                            {
                                                field: "MeOS information server address",
                                                test_button: "Test"
                                            }
                                        }
                                    }
                                },
                                update_results:
                                {
                                    header: "Update Results",
                                    item:
                                    {
                                        working_directory:
                                        {
                                            labels:
                                            {
                                                field: "Working Directory",
                                                path_button: "..."
                                            }
                                        }
                                    }
                                },
                                log:
                                {
                                    header: "Log"
                                }
                            }
                        }
                    }
                },
                division_result_server:
                {
                    name: "Division Result Server",
                    route:
                    {
                        repo: "https://github.com/Thomilist/division-result-server"
                    }
                }
            }
        },
        wikipedia:
        {
            name: "Wikipedia",
            page:
            {
                cgnat:
                {
                    name: "CGNAT",
                    route: "https://en.wikipedia.org/wiki/Carrier-grade_NAT"
                }
            }
        }
    },
    misc:
    {
        cpu_arch:
        {
            x86_64: "x86-64"
        },
        requirements:
        {
            storage: "~100 MB"
        }
    }
}