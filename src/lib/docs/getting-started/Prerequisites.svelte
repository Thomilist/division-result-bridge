<script lang="ts">
	import type { DocPageProps } from "$lib/types";
	import DocHeader from "../DocHeader.svelte";
	import { resources } from "$lib/resources";
	import DocElement from "../DocElement.svelte";

    export let props: DocPageProps;

	const program = resources.external.thomilist.project.division_result_bridge;
</script>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "main", "intro"],
    values:
    {
        bridge_name: program.name
    }
}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "requirements", "title"], docpage: props}}/>

<DocHeader props={{depth: 3, specifiers: ["section", "requirements", "section", "system", "title"], docpage: props}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "requirements", "section", "system", "intro"],
    values:
    {
        bridge_name: program.name
    }
}}/>

<ul>
	<DocElement props={
	{
		element: "li",
		docpage: props,
		specifiers: ["section", "requirements", "section", "system", "req0"],
		values:
		{
			win: resources.external.microsoft.project.windows.name
		}
	}}/>
	<DocElement props={
	{
		element: "li",
		docpage: props,
		specifiers: ["section", "requirements", "section", "system", "req1"],
		values:
		{
			storage: resources.misc.requirements.storage
		}
	}}/>
	<DocElement props={
	{
		element: "li",
		docpage: props,
		specifiers: ["section", "requirements", "section", "system", "req2"]
	}}/>
	<DocElement props={
	{
		element: "li",
		docpage: props,
		specifiers: ["section", "requirements", "section", "system", "req3"],
		values:
		{
			cpu_arch: resources.misc.cpu_arch.x86_64
		}
	}}/>
</ul>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "requirements", "section", "system", "other_systems"],
    values:
    {
        win: resources.external.microsoft.project.windows.name,
		win10: resources.external.microsoft.project.windows10.name,
		cpu_arch: resources.misc.cpu_arch.x86_64
    }
}}/>

<DocHeader props={{depth: 3, specifiers: ["section", "requirements", "section", "surrounding-setup", "title"], docpage: props}}/>

<DocElement props={
{
    docpage: props,
    specifiers: ["section", "requirements", "section", "surrounding-setup", "intro"],
    values:
    {
        bridge_name: program.name
    }
}}/>

<ul>
	<DocElement props={
	{
		element: "li",
		docpage: props,
		specifiers: ["section", "requirements", "section", "surrounding-setup", "req0"],
		values:
		{
			divi_link: resources.external.andersklinting.project.divisionsmatchberegning.route.repo,
			divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name
		}
	}}/>
	<DocElement props={
	{
		element: "li",
		docpage: props,
		specifiers: ["section", "requirements", "section", "surrounding-setup", "req1"],
		values:
		{
			server_link: resources.external.thomilist.project.division_result_server.route.repo,
			server_name: resources.external.thomilist.project.division_result_server.name
		}
	}}/>
</ul>

<DocElement props={
{
	docpage: props,
	specifiers: ["section", "requirements", "section", "surrounding-setup", "optional"],
	values:
	{
		bridge_name: program.name
	}
}}/>

<ul>
	<DocElement props={
	{
		element: "li",
		docpage: props,
		specifiers: ["section", "requirements", "section", "surrounding-setup", "opt0"],
		values:
		{
			meos_link: resources.external.melinsoftware.project.meos.route.website,
			meos_name: resources.external.melinsoftware.project.meos.name,
			meos_minimum_version: resources.external.melinsoftware.project.meos.version.infoserver
		}
	}}/>
	<DocElement props={
	{
		element: "li",
		docpage: props,
		specifiers: ["section", "requirements", "section", "surrounding-setup", "opt1"],
		values:
		{
			result_format: resources.external.iof.project.iof_xml_3.name
		}
	}}/>
</ul>