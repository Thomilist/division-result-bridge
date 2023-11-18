<script lang="ts">
	import type { DocPageProps } from "$lib/types";
	import { t } from "svelte-intl-precompile";
	import DocHeader from "../DocHeader.svelte";
	import { tpage } from "../docs";
	import { resources } from "$lib/resources";
	import { base } from "$app/paths";

    export let props: DocPageProps;
</script>

<p>
	{@html $t(tpage(props, ["intro"]), {values:
	{
		bridge_name: resources.external.thomilist.project.division_result_bridge.name
	}})}
</p>

<DocHeader props={{depth: 2, specifiers: ["section", "fresh-install", "title"], docpage: props}}/>

<p>
	{@html $t(tpage(props, ["section", "fresh-install", "download"]), {values:
	{
		download_page_link: `${base}${resources.internal.download.route}`
	}})}
</p>

<p>
	{@html $t(tpage(props, ["section", "fresh-install", "extract"]), {values:
	{
		bridge_name: resources.external.thomilist.project.division_result_bridge.name,
		bridge_exe_name: resources.external.thomilist.project.division_result_bridge.exe_name
	}})}
</p>

<DocHeader props={{depth: 2, specifiers: ["section", "update", "title"], docpage: props}}/>

<p>
	{@html $t(tpage(props, ["section", "update", "main"]))}
</p>

<p>
	{@html $t(tpage(props, ["section", "update", "settings"]), {values:
	{
		win: resources.external.microsoft.project.windows.name
	}})}
</p>

<p>
	{@html $t(tpage(props, ["section", "update", "semver"]), {values:
	{
		bridge_name: resources.external.thomilist.project.division_result_bridge.name,
		semver_link: resources.external.semver.project.semver.route.website
	}})}
</p>