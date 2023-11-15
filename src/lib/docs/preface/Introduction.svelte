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
	{@html $t(tpage(props, ["section", "main", "welcome"]), {values:
	{
		bridge_name: resources.external.thomilist.project.division_result_bridge.name,
		getting_started_link: `${base}${resources.internal.docs.collection.getting_started.page.route.prerequisites}`
	}})}
</p>

<DocHeader props={{depth: 2, specifiers: ["section", "what", "title"], docpage: props}}/>

<p>
	{@html $t(tpage(props, ["section", "what", "description"]), {values:
	{
		bridge_name: resources.external.thomilist.project.division_result_bridge.name,
		divi_link: resources.external.andersklinting.project.divisionsmatchberegning.route.repo,
		divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name,
		server_link: resources.external.thomilist.project.division_result_server.route.repo,
		server_name: resources.external.thomilist.project.division_result_server.name
	}})}
</p>

<DocHeader props={{depth: 2, specifiers: ["section", "motivation", "title"], docpage: props}}/>

<p>
	{@html $t(tpage(props, ["section", "motivation", "live-results"]), {values:
	{
		liveresults_link: resources.external.liveresults.project.liveresults.route.website,
		liveresults_name: resources.external.liveresults.project.liveresults.name
	}})}
</p>

<p>
	{@html $t(tpage(props, ["section", "motivation", "division-matches"]), {values:
	{
		divi_link: resources.external.andersklinting.project.divisionsmatchberegning.route.repo,
		divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name
	}})}
</p>

<p>
	{@html $t(tpage(props, ["section", "motivation", "problem"]), {values:
	{
		divi_link: resources.external.andersklinting.project.divisionsmatchberegning.route.repo,
		divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name,
		cgnat_link: resources.external.wikipedia.page.cgnat.route,
		cgnat_name: resources.external.wikipedia.page.cgnat.name
	}})}
</p>

<p>
	{@html $t(tpage(props, ["section", "motivation", "solution"]), {values:
	{
		bridge_name: resources.external.thomilist.project.division_result_bridge.name,
		server_link: resources.external.thomilist.project.division_result_server.route.repo,
		server_name: resources.external.thomilist.project.division_result_server.name
	}})}
</p>