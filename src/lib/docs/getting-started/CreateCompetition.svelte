<script lang="ts">
    import Image from "$lib/Image.svelte";
    import * as first_launch from "$lib/assets/interface/first-launch.png";
    import * as page1 from "$lib/assets/interface/comp-wizard/page1.png";
    import * as page2 from "$lib/assets/interface/comp-wizard/page2.png";
    import * as page3 from "$lib/assets/interface/comp-wizard/page3.png";
    import * as page4 from "$lib/assets/interface/comp-wizard/page4.png";
    import * as page5 from "$lib/assets/interface/comp-wizard/page5.png";
    import * as page5_error from "$lib/assets/interface/comp-wizard/page5-error.png";
    import * as page6 from "$lib/assets/interface/comp-wizard/page6.png";
	import { resources } from "$lib/resources";
	import type { DocPageProps } from "$lib/types";
	import { tpage } from "../docs";
	import { t } from "svelte-intl-precompile";
	import DocElement from "../DocElement.svelte";
	import DocHeader from "../DocHeader.svelte";

    export let props: DocPageProps;

    const program = resources.external.thomilist.project.division_result_bridge;
</script>

<DocElement props={
{
    docpage: props,
    specifiers: ["launch"],
    values:
    {
        bridge_name: program.name
    }
}}/>

<Image props={
{
    src: first_launch.default,
    alt: $t(tpage(props, ["initial-interface-alt"]), {values:
	{
		bridge_name: program.name
	}})
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page1", "open-wizard"],
    values:
    {
        comp_menu: program.interface.menu_bar.competition.label,
        create_new: program.interface.menu_bar.competition.item.create_new.label
    }
}}/>

<Image props={
{
    src: page1.default,
    alt: $t(tpage(props, ["section", "page1", "alt"]))
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page1", "next"],
    values:
    {
        next: program.interface.comp_wizard.button.next.label
    }
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "page2", "title"], docpage: props}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page2", "intro"]
}}/>

<Image props={
{
    src: page2.default,
    alt: $t(tpage(props, ["section", "page2", "alt"]))
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page2", "meaning"],
    values:
    {
        bridge_name: program.name
    }
}}/>

<DocHeader props={{depth: 3, specifiers: ["section", "page2", "section", "meos-divi", "title"], docpage: props, values: {meos_divi_title: program.interface.comp_wizard.page.compatibility.meos_divi}}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page2", "section", "meos-divi", "what"],
    values:
    {
        bridge_name: program.name,
        meos_name: resources.external.melinsoftware.project.meos.name
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page2", "section", "meos-divi", "how"],
    values:
    {
        bridge_name: program.name,
        divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name,
        meos_name: resources.external.melinsoftware.project.meos.name
    }
}}/>

<DocHeader props={{depth: 3, specifiers: ["section", "page2", "section", "divi", "title"], docpage: props, values: {divi_title: program.interface.comp_wizard.page.compatibility.divi}}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page2", "section", "divi", "what"],
    values:
    {
        divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name,
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page2", "section", "divi", "how"],
    values:
    {
        bridge_name: program.name,
        divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name,
    }
}}/>

<DocHeader props={{depth: 3, specifiers: ["section", "page2", "section", "xml-divi", "title"], docpage: props, values: {xml_divi_title: program.interface.comp_wizard.page.compatibility.xml_divi}}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page2", "section", "xml-divi", "what"],
    values:
    {
        bridge_name: program.name,
        divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name,
        iof_xml: resources.external.iof.project.iof_xml_3.name
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page2", "section", "xml-divi", "how"],
    values:
    {
        bridge_name: program.name,
        divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name,
        meos_name: resources.external.melinsoftware.project.meos.name
    }
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "page3", "title"], docpage: props}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page3", "intro"]
}}/>

<ul>
	<DocElement props={
	{
		element: "li",
		docpage: props,
		specifiers: ["section", "page3", "insecure"]
	}}/>
	<DocElement props={
	{
		element: "li",
		docpage: props,
		specifiers: ["section", "page3", "immutable"]
	}}/>
</ul>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page3", "implication"]
}}/>

<Image props={
{
    src: page3.default,
    alt: $t(tpage(props, ["section", "page3", "alt"]), {values: {example_password: program.interface.example.password}})
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page3", "purpose"]
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "page4", "title"], docpage: props}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page4", "intro"],
    values:
    {
        server_link: resources.external.thomilist.project.division_result_server.route.repo,
        server_name: resources.external.thomilist.project.division_result_server.name
    }
}}/>

<Image props={
{
    src: page4.default,
    alt: $t(tpage(props, ["section", "page4", "alt"]), {values: {example_server_address: program.interface.example.server_address}})
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page4", "default"],
    values:
    {
        next: program.interface.comp_wizard.button.next.label
    }
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "page5", "title"], docpage: props}}/>

<DocHeader props={{depth: 3, specifiers: ["section", "page5", "section", "success", "title"], docpage: props}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page5", "section", "success", "intro"],
    values:
    {
        server_link: resources.external.thomilist.project.division_result_server.route.repo,
        server_name: resources.external.thomilist.project.division_result_server.name
    }
}}/>

<Image props={
{
    src: page5.default,
    alt: $t(tpage(props, ["section", "page5", "section", "success", "alt"]))
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page5", "section", "success", "next"]
}}/>

<DocHeader props={{depth: 3, specifiers: ["section", "page5", "section", "error", "title"], docpage: props}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page5", "section", "error", "intro"],
    values:
    {
        response_title: program.interface.comp_wizard.page.response.title
    }
}}/>

<Image props={
{
    src: page5_error.default,
    alt: $t(tpage(props, ["section", "page5", "section", "error", "alt"]))
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page5", "section", "error", "troubleshooting"],
    values:
    {
        next: program.interface.comp_wizard.button.next.label,
        server_link: resources.external.thomilist.project.division_result_server.route.repo,
        server_name: resources.external.thomilist.project.division_result_server.name
    }
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "page6", "title"], docpage: props}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page6", "intro"]
}}/>

<Image props={
{
    src: page6.default,
    alt: $t(tpage(props, ["section", "page6", "alt"]))
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page6", "use-now"],
    values:
    {
        use_now: program.interface.comp_wizard.page.summary.use_now,
        bridge_name: program.name,
        finish: program.interface.comp_wizard.button.finish.label
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "page6", "use-later"],
    values:
    {
        use_now: program.interface.comp_wizard.page.summary.use_now
    }
}}/>