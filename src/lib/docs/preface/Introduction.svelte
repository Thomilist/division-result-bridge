<script lang="ts">
	import type { DocPageProps } from "$lib/types";
	import DocHeader from "../DocHeader.svelte";
	import { resources } from "$lib/resources";
	import { base } from "$app/paths";
	import DocElement from "../DocElement.svelte";

    export let props: DocPageProps;

	const program = resources.external.thomilist.project.division_result_bridge;
</script>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "main", "welcome"],
    values:
    {
        bridge_name: program.name,
		getting_started_link: `${base}${resources.internal.docs.collection.getting_started.page.route.prerequisites}`
    }
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "what", "title"], docpage: props}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "what", "description"],
    values:
    {
        bridge_name: program.name,
		divi_link: resources.external.andersklinting.project.divisionsmatchberegning.route.repo,
		divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name,
		server_link: resources.external.thomilist.project.division_result_server.route.repo,
		server_name: resources.external.thomilist.project.division_result_server.name
    }
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "motivation", "title"], docpage: props}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "motivation", "live-results"],
    values:
    {
        liveresults_link: resources.external.liveresults.project.liveresults.route.website,
		liveresults_name: resources.external.liveresults.project.liveresults.name
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "motivation", "division-matches"],
    values:
    {
        divi_link: resources.external.andersklinting.project.divisionsmatchberegning.route.repo,
		divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "motivation", "problem"],
    values:
    {
        divi_link: resources.external.andersklinting.project.divisionsmatchberegning.route.repo,
		divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name,
		cgnat_link: resources.external.wikipedia.page.cgnat.route,
		cgnat_name: resources.external.wikipedia.page.cgnat.name
    }
}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "motivation", "solution"],
    values:
    {
        bridge_name: program.name,
		server_link: resources.external.thomilist.project.division_result_server.route.repo,
		server_name: resources.external.thomilist.project.division_result_server.name
    }
}}/>