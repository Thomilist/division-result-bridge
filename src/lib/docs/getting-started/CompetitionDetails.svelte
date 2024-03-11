<script lang="ts">
	import * as img_result_source_configured from "$lib/assets/interface/result-source-configured/meos-divi/interface.png";
	import * as img_competition_pane_highlighted from "$lib/assets/interface/result-source-configured/meos-divi/competition-pane-highlighted.png";
	import * as img_import_metadata_highlighted from "$lib/assets/interface/result-source-configured/meos-divi/import-metadata-highlighted.png";
	import * as img_import_metadata_response from "$lib/assets/interface/comp-configured/import-metadata-response.png";
	import * as img_divisions_pane_highlighted from "$lib/assets/interface/comp-configured/meos-divi/divisions-highlighted.png";
	import * as img_new_divi_divi_file from "$lib/assets/interface/comp-configured/meos-divi/create-new-division.png";
	import * as img_new_divi_info_server from "$lib/assets/interface/comp-configured/divi/create-new-division.png";
	import * as img_divi_print_setup from "$lib/assets/divisionsmatchberegning/print-setup-layout-highlighted.png";
	import * as img_divi_info_server from "$lib/assets/divisionsmatchberegning/info-server.png";
    import * as img_liveresults_field_highlighted from "$lib/assets/interface/divisions-configured/meos-divi/liveresults-field-highlighted.png";
    import * as img_update_metadata_response from "$lib/assets/interface/fully-configured/meos-divi/update-metadata-response.png";
    import * as img_validate_highlighted from "$lib/assets/interface/fully-configured/meos-divi/validate-highlighted.png";
    import * as img_validate_response from "$lib/assets/interface/validated/validate-response.png";
    import * as img_online_buttons_highlighted from "$lib/assets/interface/validated/meos-divi/online-buttons-highlighted.png";
    import { resources } from "$lib/resources";
	import type { DocPageProps } from "$lib/types";
	import DocElement from "../DocElement.svelte";
	import DocHeader from "../DocHeader.svelte";
	import DocImage from "../DocImage.svelte";
	import DocHighlightedTextbox from "../DocHighlightedTextbox.svelte";

    export let props: DocPageProps;

    const program = resources.external.thomilist.project.division_result_bridge;
</script>



<DocElement props=
{{
    docpage: props,
    specifiers: ["intro"],
    values:
    {
        meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label
    }
}}/>

<DocImage props=
{{
    src: img_result_source_configured.default,
    docpage: props,
    specifiers: ["image", "result-source-configured"]
}}/>

<DocElement props=
{{
    docpage: props,
    specifiers: ["empty-fields"],
    values:
    {
        competition: program.interface.main.pane.competition.header,
        divisions: program.interface.main.pane.divisions.header,
        online: program.interface.main.pane.online.header
    }
}}/>



<DocHeader props=
{{
    depth: 2,
    specifiers: ["section", "competition", "title"],
    docpage: props
}}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "competition", "intro"],
        values:
        {
            competition: program.interface.main.pane.competition.header
        }
    }}/>
    
    <DocImage props=
    {{
        src: img_competition_pane_highlighted.default,
        docpage: props,
        specifiers: ["section", "competition", "image", "competition"],
        values:
        {
            common:
            {
                competition: program.interface.main.pane.competition.header
            }
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "competition", "credentials"],
        values:
        {
            comp_id: program.interface.main.pane.competition.item.comp_id.label.field,
            password: program.interface.main.pane.competition.item.password.label.field
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "competition", "metadata"],
        values:
        {
            name: program.interface.main.pane.competition.item.name.label.field,
            organiser: program.interface.main.pane.competition.item.organiser.label.field,
            date: program.interface.main.pane.competition.item.date.label.field,
            timezone: program.interface.main.pane.competition.item.timezone.label.field,
            bridge_name: program.name
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "competition", "datetime-purpose"]
    }}/>

    <DocHighlightedTextbox style="tip">
        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "competition", "metadata-meos"],
            values:
            {
                meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label,
                meos_name: resources.external.melinsoftware.project.meos.name,
                competition_menu: program.interface.menu_bar.competition.label,
                import_metadata: program.interface.menu_bar.competition.item.import_metadata.label
            }
        }}/>
        
        <DocImage props=
        {{
            src: img_import_metadata_highlighted.default,
            docpage: props,
            specifiers: ["section", "competition", "image", "import-metadata"],
            values:
            {
                common:
                {
                    competition_menu: program.interface.menu_bar.competition.label,
                    import_metadata: program.interface.menu_bar.competition.item.import_metadata.label
                }
            }
        }}/>

        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "competition", "metadata-meos-success"],
            values:
            {
                meos_name: resources.external.melinsoftware.project.meos.name,
                bridge_name: program.name
            }
        }}/>
        
        <DocImage props=
        {{
            src: img_import_metadata_response.default,
            docpage: props,
            specifiers: ["section", "competition", "image", "import-metadata-response"],
            values:
            {
                common:
                {
                    meos_name: resources.external.melinsoftware.project.meos.name
                }
            }
        }}/>
    </DocHighlightedTextbox>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "competition", "visibility"],
        values:
        {
            competition: program.interface.main.pane.competition.header,
            visibility: program.interface.main.pane.competition.item.visibility.label.field
        }
    }}/>
    
    <table class="basic-table">
        <tr>
            <td class="named">
                {program.interface.main.pane.competition.item.visibility.label.private}
            </td>
            <DocElement props=
            {{
                element: "td",
                docpage: props,
                specifiers: ["section", "competition", "visibility-private"]
            }}/>
        </tr>
        <tr>
            <td class="named">
                {program.interface.main.pane.competition.item.visibility.label.hidden}
            </td>
            <DocElement props=
            {{
                element: "td",
                docpage: props,
                specifiers: ["section", "competition", "visibility-hidden"]
            }}/>
        </tr>
        <tr>
            <td class="named">
                {program.interface.main.pane.competition.item.visibility.label.public}
            </td>
            <DocElement props=
            {{
                element: "td",
                docpage: props,
                specifiers: ["section", "competition", "visibility-public"]
            }}/>
        </tr>
    </table>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "competition", "visibility-change"],
        values:
        {
            visibility_hidden: program.interface.main.pane.competition.item.visibility.label.hidden,
            bridge_name: program.name
        }
    }}/>



<DocHeader props=
{{
    depth: 2,
    specifiers: ["section", "divisions", "title"],
    docpage: props
}}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "divisions", "intro"],
        values:
        {
            divisions: program.interface.main.pane.divisions.header,
            new_button: program.interface.main.pane.divisions.item.new.label.button,
            edit_button: program.interface.main.pane.divisions.item.edit.label.button,
            delete_button: program.interface.main.pane.divisions.item.delete.label.button
        }
    }}/>

    <DocImage props=
    {{
        src: img_divisions_pane_highlighted.default,
        docpage: props,
        specifiers: ["section", "divisions", "image", "divisions"],
        values:
        {
            common:
            {
                divisions: program.interface.main.pane.divisions.header
            }
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "divisions", "new-divi-divi-file"],
        values:
        {
            meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label,
            xml_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.xml_divi.label,
            divi_id: program.interface.divi_editor.item.divi_id.label.field,
            name: program.interface.divi_editor.item.name.label.field,
            divi_config_path: program.interface.divi_editor.item.divi_config_path.label.field
        }
    }}/>

    <DocImage props=
    {{
        src: img_new_divi_divi_file.default,
        docpage: props,
        specifiers: ["section", "divisions", "image", "new-divi-divi-file"],
        values:
        {
            common:
            {
                meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label,
                xml_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.xml_divi.label
            }
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "divisions", "new-divi-info-server"],
        values:
        {
            divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label,
            divi_config_path: program.interface.divi_editor.item.divi_config_path.label.field,
            info_server_address: program.interface.divi_editor.item.info_server_address.label.field
        }
    }}/>

    <DocImage props=
    {{
        src: img_new_divi_info_server.default,
        docpage: props,
        specifiers: ["section", "divisions", "image", "new-divi-info-server"],
        values:
        {
            common:
            {
                divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label
            }
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "divisions", "divi-editor-field-divi-id"],
        values:
        {
            comp_id: program.interface.main.pane.competition.item.comp_id.label.field,
            divi_id: program.interface.divi_editor.item.divi_id.label.field
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "divisions", "divi-editor-field-name"],
        values:
        {
            divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "divisions", "divi-editor-field-divi-file"],
        values:
        {
            divi_config_path: program.interface.divi_editor.item.divi_config_path.label.field,
            divi: resources.external.andersklinting.project.divisionsmatchberegning.name
        }
    }}/>

    <DocHighlightedTextbox style="warning">
        <DocElement props=
        {{
            docpage: props,
            specifiers: ["section", "divisions", "divi-file-warning"],
            values:
            {
                divi: resources.external.andersklinting.project.divisionsmatchberegning.name,
                print: resources.external.andersklinting.project.divisionsmatchberegning.interface.menu_bar.print.label,
                setup: resources.external.andersklinting.project.divisionsmatchberegning.interface.menu_bar.print.item.setup.label,
                html_css: resources.external.andersklinting.project.divisionsmatchberegning.interface.print_setup.item.html_css.label,
                layout: resources.external.andersklinting.project.divisionsmatchberegning.interface.print_setup.item.layout.label,
                blue: resources.external.andersklinting.project.divisionsmatchberegning.interface.print_setup.item.layout.item.blue.label,
                bridge_name: program.name
            }
        }}/>

        <DocImage props=
        {{
            src: img_divi_print_setup.default,
            docpage: props,
            specifiers: ["section", "divisions", "image", "divi-print-setup"],
            values:
            {
                common:
                {
                    divi: resources.external.andersklinting.project.divisionsmatchberegning.name
                }
            }
        }}/>
    </DocHighlightedTextbox>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "divisions", "divi-editor-field-info-server"],
        values:
        {
            divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label,
            info_server_address: program.interface.divi_editor.item.info_server_address.label.field,
            divi: resources.external.andersklinting.project.divisionsmatchberegning.name,
            info: resources.external.andersklinting.project.divisionsmatchberegning.interface.menu_bar.info.label,
            info_server: resources.external.andersklinting.project.divisionsmatchberegning.interface.menu_bar.info.item.info_server.label
        }
    }}/>

    <DocImage props=
    {{
        src: img_divi_info_server.default,
        docpage: props,
        specifiers: ["section", "divisions", "image", "divi-info-server"],
        values:
        {
            common:
            {
                divi: resources.external.andersklinting.project.divisionsmatchberegning.name
            }
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "divisions", "new-divi-save"],
        values:
        {
            save_button: program.interface.divi_editor.button.save.label,
            new_button: program.interface.main.pane.divisions.item.new.label.button,
            edit_button: program.interface.main.pane.divisions.item.edit.label.button,
            delete_button: program.interface.main.pane.divisions.item.delete.label.button
        }
    }}/>



<DocHeader props=
{{
    depth: 2,
    specifiers: ["section", "liveresults", "title"],
    docpage: props,
    values:
    {
        liveresults_name: resources.external.liveresults.project.liveresults.name
    }
}}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "liveresults", "intro"],
        values:
        {
            liveresults_link: resources.external.liveresults.project.liveresults.route.website,
            liveresults_name: resources.external.liveresults.project.liveresults.name
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "liveresults", "add-link"],
        values:
        {
            liveresults_name: resources.external.liveresults.project.liveresults.name,
            online: program.interface.main.pane.online.header,
            liveresults_id: program.interface.main.pane.online.item.liveresults.label.field
        }
    }}/>

    <DocImage props=
    {{
        src: img_liveresults_field_highlighted.default,
        docpage: props,
        specifiers: ["section", "liveresults", "image", "liveresults-field-highlighted"],
        values:
        {
            common:
            {
                online: program.interface.main.pane.online.header
            },
            alt:
            {
                liveresults_id: program.interface.main.pane.online.item.liveresults.label.field
            },
            caption:
            {
                liveresults_name: resources.external.liveresults.project.liveresults.name
            }
        }
    }}/>



<DocHeader props=
{{
    depth: 2,
    specifiers: ["section", "validate-configuration", "title"],
    docpage: props
}}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "validate-configuration", "intro"],
        values:
        {
            bridge_name: program.name
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "validate-configuration", "validate-manually"],
        values:
        {
            competition: program.interface.menu_bar.competition.label,
            validate: program.interface.menu_bar.competition.item.validate.label
        }
    }}/>

    <DocImage props=
    {{
        src: img_validate_highlighted.default,
        docpage: props,
        specifiers: ["section", "validate-configuration", "image", "validate-highlighted"],
        values:
        {
            common:
            {
                competition: program.interface.menu_bar.competition.label
            },
            alt:
            {
                validate: program.interface.menu_bar.competition.item.validate.label
            }
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "validate-configuration", "validate-response"]
    }}/>

    <DocImage props=
    {{
        src: img_validate_response.default,
        docpage: props,
        specifiers: ["section", "validate-configuration", "image", "validate-response"]
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "validate-configuration", "validate-at-startup"],
        values:
        {
            bridge_name: program.name
        }
    }}/>



<DocHeader props=
{{
    depth: 2,
    specifiers: ["section", "upload-your-changes", "title"],
    docpage: props
}}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "upload-your-changes", "intro"],
        values:
        {
            visibility: program.interface.main.pane.competition.item.visibility.label.field,
            online: program.interface.main.pane.online.header
        }
    }}/>

    <DocImage props=
    {{
        src: img_online_buttons_highlighted.default,
        docpage: props,
        specifiers: ["section", "upload-your-changes", "image", "online-buttons-highlighted"],
        values:
        {
            common:
            {
                online: program.interface.main.pane.online.header
            }
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "upload-your-changes", "update-metadata"],
        values:
        {
            update_metadata: program.interface.main.pane.online.item.manage_on_server.label.button.update_metadata,
            division_result_server: resources.external.thomilist.project.division_result_server.name
        }
    }}/>

    <DocImage props=
    {{
        src: img_update_metadata_response.default,
        docpage: props,
        specifiers: ["section", "upload-your-changes", "image", "update-metadata-response"],
        values:
        {
            common:
            {
                division_result_server: resources.external.thomilist.project.division_result_server.name
            }
        }
    }}/>

    <DocElement props=
    {{
        docpage: props,
        specifiers: ["section", "upload-your-changes", "view-in-browser"],
        values:
        {
            view_in_browser: program.interface.main.pane.online.item.inspect_on_server.label.button.view_in_browser
        }
    }}/>
