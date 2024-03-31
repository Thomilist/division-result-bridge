<script lang="ts">
	import { resources } from "$lib/resources";
	import type { DocPageProps } from "$lib/types";
	import DocElement from "../DocElement.svelte";
	import DocHeader from "../DocHeader.svelte";
    import DocImage from "../DocImage.svelte";
	import { locale } from "svelte-intl-precompile";
    import * as img_en_meos_services_tab from "$lib/assets/meos/en_services-tab-punching-test-highlighted.png";
    import * as img_da_meos_services_tab from "$lib/assets/meos/da_services-tab-punching-test-highlighted.png";
    import * as img_update_results_highlighted from "$lib/assets/interface/validated/meos-divi/update-results-pane-highlighted.png";
    import * as img_results_updated from "$lib/assets/interface/validated/meos-divi/results-updated.png";
    import * as img_delete_results_highlighted from "$lib/assets/interface/validated/meos-divi/delete-results-button-highlighted.png";

    export let props: DocPageProps;

    const program = resources.external.thomilist.project.division_result_bridge;

    const img_meos_services_tab = new Map([
        ["en", img_en_meos_services_tab],
        ["da", img_da_meos_services_tab]
    ]);
</script>



<DocElement props=
{{
    docpage: props,
    specifiers: ["intro"],
    values:
    {
        
    }
}}/>



<DocHeader props=
{{
    depth: 2,
    specifiers: ["section", "fake-results", "title"],
    docpage: props
}}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "fake-results", "intro"]
    }}/>



    <DocHeader props=
    {{
        depth: 3,
        specifiers: ["section", "fake-results", "section", "manual", "title"],
        docpage: props
    }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "fake-results", "section", "manual", "intro"],
            values:
            {
                iof_xml: resources.external.iof.project.iof_xml_3.name
            }
        }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "fake-results", "section", "manual", "scaling"]
        }}/>



    <DocHeader props=
    {{
        depth: 3,
        specifiers: ["section", "fake-results", "section", "automatic", "title"],
        docpage: props
    }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "fake-results", "section", "automatic", "intro"]
        }}/>



        <DocHeader props=
        {{
            depth: 4,
            specifiers: ["section", "fake-results", "section", "automatic", "section", "meos-divi", "title"],
            docpage: props,
            values:
            {
                meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label
            }
        }}/>

            <DocElement props=
            {{
                docpage: props,
                specifiers: ["section", "fake-results", "section", "automatic", "section", "meos-divi", "intro"],
                values:
                {
                    meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label,
                    meos: resources.external.melinsoftware.project.meos.name
                }
            }}/>

            <DocElement props=
            {{
                docpage: props,
                specifiers: ["section", "fake-results", "section", "automatic", "section", "meos-divi", "prepare"]
            }}/>

            <ul>
                <DocElement props=
                {{
                    element: "li",
                    docpage: props,
                    specifiers: ["section", "fake-results", "section", "automatic", "section", "meos-divi", "prep0"],
                    values:
                    {
                        meos: resources.external.melinsoftware.project.meos.name
                    }
                }}/>

                <DocElement props=
                {{
                    element: "li",
                    docpage: props,
                    specifiers: ["section", "fake-results", "section", "automatic", "section", "meos-divi", "prep1"],
                    values:
                    {
                        meos: resources.external.melinsoftware.project.meos.name
                    }
                }}/>

                <DocElement props=
                {{
                    element: "li",
                    docpage: props,
                    specifiers: ["section", "fake-results", "section", "automatic", "section", "meos-divi", "prep2"],
                    values:
                    {
                        meos: resources.external.melinsoftware.project.meos.name
                    }
                }}/>
            </ul>

            <DocElement props=
            {{
                docpage: props,
                specifiers: ["section", "fake-results", "section", "automatic", "section", "meos-divi", "find-punching-test"],
                values:
                {
                    meos: resources.external.melinsoftware.project.meos.name
                }
            }}/>

            <DocImage props=
            {{
                src: `${img_meos_services_tab.get($locale)?.default}`,
                docpage: props,
                specifiers: ["section", "fake-results", "section", "automatic", "section", "meos-divi", "image", "meos-services-tab"],
                values:
                {
                    common:
                    {
                        meos: resources.external.melinsoftware.project.meos.name
                    }
                }
            }}/>

            <DocElement props=
            {{
                docpage: props,
                specifiers: ["section", "fake-results", "section", "automatic", "section", "meos-divi", "run-punching-test"]
            }}/>



<DocHeader props=
{{
    depth: 2,
    specifiers: ["section", "prepare-publishing-pipeline", "title"],
    docpage: props
}}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "prepare-publishing-pipeline", "intro"]
    }}/>

    <ul>
        <DocElement props=
        {{
            element: "li",
            docpage: props,
            specifiers: ["section", "prepare-publishing-pipeline", "check0"],
            values:
            {
                bridge_name: program.name
            }
        }}/>
        
        <DocElement props=
        {{
            element: "li",
            docpage: props,
            specifiers: ["section", "prepare-publishing-pipeline", "check1"],
            values:
            {
                division_result_server: resources.external.thomilist.project.division_result_server.name
            }
        }}/>
        
        <DocElement props=
        {{
            element: "li",
            docpage: props,
            specifiers: ["section", "prepare-publishing-pipeline", "check2"]
        }}/>
    </ul>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "prepare-publishing-pipeline", "more-detail"]
    }}/>



    <DocHeader props=
    {{
        depth: 3,
        specifiers: ["section", "prepare-publishing-pipeline", "section", "meos-divi", "title"],
        docpage: props,
        values:
        {
            meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label
        }
    }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "prepare-publishing-pipeline", "section", "meos-divi", "intro"],
            values:
            {
                meos: resources.external.melinsoftware.project.meos.name,
                divi: resources.external.andersklinting.project.divisionsmatchberegning.name
            }
        }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "prepare-publishing-pipeline", "section", "meos-divi", "meos"],
            values:
            {
                meos: resources.external.melinsoftware.project.meos.name,
                bridge_name: program.name
            }
        }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "prepare-publishing-pipeline", "section", "meos-divi", "divi"],
            values:
            {
                divi: resources.external.andersklinting.project.divisionsmatchberegning.name,
                bridge_name: program.name
            }
        }}/>



    <DocHeader props=
    {{
        depth: 3,
        specifiers: ["section", "prepare-publishing-pipeline", "section", "divi", "title"],
        docpage: props,
        values:
        {
            divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label
        }
    }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "prepare-publishing-pipeline", "section", "divi", "intro"],
            values:
            {
                divi: resources.external.andersklinting.project.divisionsmatchberegning.name,
                bridge_name: program.name
            }
        }}/>



    <DocHeader props=
    {{
        depth: 3,
        specifiers: ["section", "prepare-publishing-pipeline", "section", "xml-divi", "title"],
        docpage: props,
        values:
        {
            xml_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.xml_divi.label
        }
    }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "prepare-publishing-pipeline", "section", "xml-divi", "intro"],
            values:
            {
                bridge_name: program.name,
                iof_xml: resources.external.iof.project.iof_xml_3.name,
                divi: resources.external.andersklinting.project.divisionsmatchberegning.name
            }
        }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "prepare-publishing-pipeline", "section", "xml-divi", "iof-xml"],
            values:
            {
                iof_xml: resources.external.iof.project.iof_xml_3.name,
                bridge_name: program.name
            }
        }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "prepare-publishing-pipeline", "section", "xml-divi", "divi"],
            values:
            {
                divi: resources.external.andersklinting.project.divisionsmatchberegning.name,
                bridge_name: program.name
            }
        }}/>



<DocHeader props=
{{
    depth: 2,
    specifiers: ["section", "upload-results", "title"],
    docpage: props
}}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "upload-results", "intro"],
        values:
        {
            update_results: program.interface.main.pane.update_results.header,
            working_directory: program.interface.main.pane.update_results.item.working_directory.label.field,
            update_interval: program.interface.main.pane.update_results.item.update_interval.label.field,
            xml_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.xml_divi.label
        }
    }}/>

    <DocImage props=
    {{
        src: img_update_results_highlighted.default,
        docpage: props,
        specifiers: ["section", "upload-results", "image", "update-results-highlighted"],
        values:
        {
            common:
            {
                update_results: program.interface.main.pane.update_results.header
            }
        }
    }}/>



    <DocHeader props=
    {{
        depth: 3,
        specifiers: ["section", "upload-results", "section", "run-once", "title"],
        docpage: props
    }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "upload-results", "section", "run-once", "intro"],
            values:
            {
                run_once: program.interface.main.pane.update_results.item.run_once.label.button,
                bridge_name: program.name,
                division_result_server: resources.external.thomilist.project.division_result_server.name
            }
        }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "upload-results", "section", "run-once", "logs"]
        }}/>

        <DocImage props=
        {{
            src: img_results_updated.default,
            docpage: props,
            specifiers: ["section", "upload-results", "section", "run-once", "image", "update-results-log"],
            values:
            {
                common:
                {
                    meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label
                }
            }
        }}/>

    

    <DocHeader props=
    {{
        depth: 3,
        specifiers: ["section", "upload-results", "section", "run-continuously", "title"],
        docpage: props
    }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "upload-results", "section", "run-continuously", "intro"]
        }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "upload-results", "section", "run-continuously", "start-stop"],
            values:
            {
                start: program.interface.main.pane.update_results.item.start.label.button,
                stop: program.interface.main.pane.update_results.item.stop.label.button
            }
        }}/>

        <DocHeader props=
        {{
            depth: 4,
            specifiers: ["section", "upload-results", "section", "run-continuously", "section", "update-interval", "title"],
            docpage: props
        }}/>

            <DocElement props=
            {{
                docpage: props,
                specifiers: ["section", "upload-results", "section", "run-continuously", "section", "update-interval", "intro"],
                values:
                {
                    xml_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.xml_divi.label,
                    iof_xml: resources.external.iof.project.iof_xml_3.name,
                    bridge_name: program.name
                }
            }}/>

            <DocElement props=
            {{
                docpage: props,
                specifiers: ["section", "upload-results", "section", "run-continuously", "section", "update-interval", "when-it-applies"],
                values:
                {
                    meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label,
                    divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label,
                    update_interval: program.interface.main.pane.update_results.item.update_interval.label.field,
                    bridge_name: program.name
                }
            }}/>

            <DocElement props=
            {{
                docpage: props,
                specifiers: ["section", "upload-results", "section", "run-continuously", "section", "update-interval", "reasons-to-decrease0"],
                values:
                {
                    meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label,
                    divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label,
                    update_interval: program.interface.main.pane.update_results.item.update_interval.label.field,
                    bridge_name: program.name
                }
            }}/>

            <DocElement props=
            {{
                docpage: props,
                specifiers: ["section", "upload-results", "section", "run-continuously", "section", "update-interval", "reasons-to-increase0"],
                values:
                {
                    divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label
                }
            }}/>

            <DocElement props=
            {{
                docpage: props,
                specifiers: ["section", "upload-results", "section", "run-continuously", "section", "update-interval", "reasons-to-increase1"],
                values:
                {
                    meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label
                }
            }}/>

            <DocElement props=
            {{
                docpage: props,
                specifiers: ["section", "upload-results", "section", "run-continuously", "section", "update-interval", "reasons-to-increase2"]
            }}/>


    

<DocHeader props=
{{
    depth: 2,
    specifiers: ["section", "upload-results", "section", "delete-results", "title"],
    docpage: props
}}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "upload-results", "section", "delete-results", "intro"]
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "upload-results", "section", "delete-results", "delete-button"],
        values:
        {
            online: program.interface.main.pane.online.header,
            delete_button: program.interface.main.pane.online.item.manage_on_server.label.button.delete_results
        }
    }}/>

    <DocImage props=
    {{
        src: img_delete_results_highlighted.default,
        docpage: props,
        specifiers: ["section", "upload-results", "section", "delete-results", "image", "delete-button"],
        values:
        {
            common:
            {
                online: program.interface.main.pane.online.header,
                delete_button: program.interface.main.pane.online.item.manage_on_server.label.button.delete_results
            }
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "upload-results", "section", "delete-results", "blank-results"]
    }}/>
