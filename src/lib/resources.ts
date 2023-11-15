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
                        home: "https://www.melin.nu/meos/en/",
                        repo: "https://github.com/melinsoftware/meos"
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
        thomilist:
        {
            name: "Thomas Emil Jensen",
            handle: "Thomilist",
            project:
            {
                division_result_bridge:
                {
                    name: "Division Result Bridge",
                    route:
                    {
                        repo: "https://github.com/Thomilist/division-result-bridge",
                        license: "https://raw.githubusercontent.com/Thomilist/division-result-bridge/main/LICENSE",
                        releases: "https://github.com/Thomilist/division-result-bridge/releases"
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
    }
}