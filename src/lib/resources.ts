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
            route: "/docs/preface/introduction"
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
            projects:
            {
                divisionsmatchberegning:
                {
                    name: "Divisionsmatchberegning",
                    routes:
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
            projects:
            {
                icons:
                {
                    name: "Bootstrap Icons",
                    routes:
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
            projects:
            {
                liveresults:
                {
                    name: "LiveResults",
                    routes:
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
            routes:
            {
                website: "https://www.mozilla.org/"
            },
            projects:
            {
                mdn:
                {
                    name: "MDN Web Docs",
                    routes:
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
            projects:
            {
                meos:
                {
                    name: "MeOS",
                    routes:
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
            routes:
            {
                website: "https://www.qt.io/"
            },
            projects:
            {
                qt6:
                {
                    name: "Qt 6",
                    routes:
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
            projects:
            {
                division_result_bridge:
                {
                    name: "Division Result Bridge",
                    routes:
                    {
                        repo: "https://github.com/Thomilist/division-result-bridge",
                        license: "https://raw.githubusercontent.com/Thomilist/division-result-bridge/main/LICENSE",
                        releases: "https://github.com/Thomilist/division-result-bridge/releases"
                    }
                },
                division_result_server:
                {
                    name: "Division Result Server",
                    routes:
                    {
                        repo: "https://github.com/Thomilist/division-result-server"
                    }
                }
            }
        }
    }
}