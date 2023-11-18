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
	specifiers: ["intro"],
	values:
	{
		bridge_name: program.name
	}
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "fresh-install", "title"], docpage: props}}/>

<DocElement props={
{
	docpage: props,
	specifiers: ["section", "fresh-install", "download"],
	values:
	{
		download_page_link: `${base}${resources.internal.download.route}`
	}
}}/>

<DocElement props={
{
	docpage: props,
	specifiers: ["section", "fresh-install", "extract"],
	values:
	{
		bridge_name: program.name,
		bridge_exe_name: program.exe_name
	}
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "update", "title"], docpage: props}}/>

<DocElement props={
{
	docpage: props,
	specifiers: ["section", "update", "main"]
}}/>

<DocElement props={
{
	docpage: props,
	specifiers: ["section", "update", "settings"],
	values:
	{
		win: resources.external.microsoft.project.windows.name
	}
}}/>

<DocElement props={
{
	docpage: props,
	specifiers: ["section", "update", "semver"],
	values:
	{
		bridbridge_name: program.name,
		semver_link: resources.external.semver.route.website
	}
}}/>