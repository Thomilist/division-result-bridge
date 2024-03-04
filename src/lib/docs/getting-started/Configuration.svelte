<script lang="ts">
    import * as img_result_source_menu from "$lib/assets/interface/comp-created/meos-divi/result-source-menu-highlighted.png"
    import * as img_working_directory from "$lib/assets/interface/comp-created/meos-divi/working-dir-field-highlighted.png";
    import * as img_comp_created_meos_divi from "$lib/assets/interface/comp-created/meos-divi/result-source-pane-highlighted.png";
    import * as img_comp_created_divi from "$lib/assets/interface/comp-created/divi/interface.png";
    import * as img_comp_created_xml_divi from "$lib/assets/interface/comp-created/xml-divi/result-source-pane-highlighted.png";
    import * as img_en_meos_services_tab from "$lib/assets/meos/en_services-tab-info-server-highlighted.png";
    import * as img_da_meos_services_tab from "$lib/assets/meos/da_services-tab-info-server-highlighted.png";
    import * as img_meos_server_test_response from "$lib/assets/interface/result-source-configured/meos-server-test-response.png";
	import { resources } from "$lib/resources";
	import type { DocPageProps } from "$lib/types";
	import DocElement from "../DocElement.svelte";
	import DocHeader from "../DocHeader.svelte";
	import DocImage from "$lib/docs/DocImage.svelte";
	import { locale } from "svelte-intl-precompile";

    export let props: DocPageProps;

    const program = resources.external.thomilist.project.division_result_bridge;

    const img_meos_services_tab = new Map([
        ["en", img_en_meos_services_tab],
        ["da", img_da_meos_services_tab]
    ]);
</script>

<DocElement props={
{
    docpage: props,
    specifiers: ["intro"],
    values:
    {
        bridge_name: program.name,
        compatibility: program.interface.menu_bar.compatibility.label,
        result_source: program.interface.menu_bar.compatibility.item.result_source.label
    }
}}/>

<DocImage props={
{
    src: img_result_source_menu.default,
    docpage: props,
    specifiers: ["image", "result-source"],
    values:
    {
        common:
        {
            compatibility: program.interface.menu_bar.compatibility.label,
            result_source: program.interface.menu_bar.compatibility.item.result_source.label
        }
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["working-directory"],
    values:
    {
        update_results: program.interface.main.pane.update_results.header,
        bridge_name: program.name,
        working_directory: program.interface.main.pane.update_results.item.working_directory.labels.field,
        path_button: program.interface.main.pane.update_results.item.working_directory.labels.path_button,
    }
}}/>

<DocImage props={
{
    src: img_working_directory.default,
    docpage: props,
    specifiers: ["image", "working-directory"],
    values:
    {
        common:
        {
            working_directory: program.interface.main.pane.update_results.item.working_directory.labels.field,
            update_results: program.interface.main.pane.update_results.header
        }
    }
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "meos-divi", "title"], docpage: props, values: {meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label}}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "meos-divi", "intro"],
    values:
    {
        result_source: program.interface.menu_bar.compatibility.item.result_source.label,
        meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label
    }
}}/>

<DocImage props={
{
    src: img_comp_created_meos_divi.default,
    docpage: props,
    specifiers: ["section", "meos-divi", "image", "comp-created"],
    values:
    {
        common:
        {
            result_source: program.interface.main.pane.result_source.header,
            meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.meos_divi.label
        }
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "meos-divi", "divi-exe-path"],
    values:
    {
        divi: resources.external.andersklinting.project.divisionsmatchberegning.name,
        bridge_name: program.name,
        path_button: program.interface.main.pane.result_source.item.divi_exe_path.labels.path_button,
        divi_exe: resources.external.andersklinting.project.divisionsmatchberegning.exe_name
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "meos-divi", "meos-server-address"],
    values:
    {
        meos_name: resources.external.melinsoftware.project.meos.name,
        meos_info_server_link: resources.external.melinsoftware.project.meos.route.info_server,
        bridge_name: program.name
    }
}}/>

<DocImage props={
{
    src: `${img_meos_services_tab.get($locale)?.default}`,
    docpage: props,
    specifiers: ["section", "meos-divi", "image", "meos-services-tab"],
    values:
    {
        common:
        {
            meos_name: resources.external.melinsoftware.project.meos.name
        }
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "meos-divi", "meos-server-test"],
    values:
    {
        test_button: program.interface.main.pane.result_source.item.meos_server_address.labels.test_button
    }
}}/>

<DocImage props={
{
    src: img_meos_server_test_response.default,
    docpage: props,
    specifiers: ["section", "meos-divi", "image", "meos-server-test-response"],
    values:
    {
        common:
        {
            meos_name: resources.external.melinsoftware.project.meos.name
        }
    }
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "divi", "title"], docpage: props, values: {meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label}}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "divi", "intro"],
    values:
    {
        result_source: program.interface.menu_bar.compatibility.item.result_source.label,
        divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label
    }
}}/>

<DocImage props={
{
    src: img_comp_created_divi.default,
    docpage: props,
    specifiers: ["section", "divi", "image", "comp-created"],
    values:
    {
        common:
        {
            result_source: program.interface.main.pane.result_source.header,
            divi_name: program.interface.menu_bar.compatibility.item.result_source.item.divi.label
        }
    }
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "xml-divi", "title"], docpage: props, values: {meos_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.xml_divi.label}}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "xml-divi", "intro"],
    values:
    {
        xml_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.xml_divi.label,
        result_source: program.interface.menu_bar.compatibility.item.result_source.label
    }
}}/>

<DocImage props={
{
    src: img_comp_created_xml_divi.default,
    docpage: props,
    specifiers: ["section", "xml-divi", "image", "comp-created"],
    values:
    {
        common:
        {
            result_source: program.interface.main.pane.result_source.header,
            xml_divi_name: program.interface.menu_bar.compatibility.item.result_source.item.xml_divi.label
        }
    }
}}/>

<DocElement props=
{{
    docpage: props,
    specifiers: ["section", "xml-divi", "divi-exe-path"],
    values:
    {
        divi: resources.external.andersklinting.project.divisionsmatchberegning.name,
        bridge_name: program.name,
        path_button: program.interface.main.pane.result_source.item.divi_exe_path.labels.path_button,
        divi_exe: resources.external.andersklinting.project.divisionsmatchberegning.exe_name
    }
}}/>

<DocElement props=
{{
    docpage: props,
    specifiers: ["section", "xml-divi", "xml-file-path"],
    values:
    {
        iof_xml: resources.external.iof.project.iof_xml_3.name,
        bridge_name: program.name,
        path_button: program.interface.main.pane.result_source.item.divi_exe_path.labels.path_button
    }
}}/>
