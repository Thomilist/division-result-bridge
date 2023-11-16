<script lang="ts">
	import type { DocPageProps } from "$lib/types";
	import { t } from "svelte-intl-precompile";
	import DocHeader from "../DocHeader.svelte";
	import { tpage } from "../docs";
	import { resources } from "$lib/resources";

    export let props: DocPageProps;
</script>

<p>
	{@html $t(tpage(props, ["section", "main", "intro"]), {values:
	{
		bridge_name: resources.external.thomilist.project.division_result_bridge.name
	}})}
</p>

<DocHeader props={{depth: 2, specifiers: ["section", "requirements", "title"], docpage: props}}/>

<DocHeader props={{depth: 3, specifiers: ["section", "requirements", "section", "system", "title"], docpage: props}}/>

<p>
	{@html $t(tpage(props, ["section", "requirements", "section", "system", "intro"]), {values:
	{
		bridge_name: resources.external.thomilist.project.division_result_bridge.name
	}})}
</p>

<ul>
	<li>
		{@html $t(tpage(props, ["section", "requirements", "section", "system", "req0"]), {values:
		{
			win: resources.external.microsoft.project.windows.name
		}})}
	</li>
	<li>
		{@html $t(tpage(props, ["section", "requirements", "section", "system", "req1"]), {values:
		{
			storage: resources.misc.requirements.storage
		}})}
	</li>
	<li>
		{@html $t(tpage(props, ["section", "requirements", "section", "system", "req2"]))}
	</li>
	<li>
		{@html $t(tpage(props, ["section", "requirements", "section", "system", "req3"]), {values:
		{
			cpu_arch: resources.misc.cpu_arch.x86_64
		}})}
	</li>
</ul>

<p>
	{@html $t(tpage(props, ["section", "requirements", "section", "system", "other_systems"]), {values:
	{
		win: resources.external.microsoft.project.windows.name,
		win10: resources.external.microsoft.project.windows10.name,
		cpu_arch: resources.misc.cpu_arch.x86_64
	}})}
</p>

<DocHeader props={{depth: 3, specifiers: ["section", "requirements", "section", "surrounding-setup", "title"], docpage: props}}/>

<p>
	{@html $t(tpage(props, ["section", "requirements", "section", "surrounding-setup", "intro"]), {values:
	{
		bridge_name: resources.external.thomilist.project.division_result_bridge.name
	}})}
</p>

<ul>
	<li>
		{@html $t(tpage(props, ["section", "requirements", "section", "surrounding-setup", "req0"]), {values:
		{
			divi_link: resources.external.andersklinting.project.divisionsmatchberegning.route.repo,
			divi_name: resources.external.andersklinting.project.divisionsmatchberegning.name
		}})}
	</li>
	<li>
		{@html $t(tpage(props, ["section", "requirements", "section", "surrounding-setup", "req1"]), {values:
		{
			server_link: resources.external.thomilist.project.division_result_server.route.repo,
			server_name: resources.external.thomilist.project.division_result_server.name
		}})}
	</li>
</ul>

<p>
	{@html $t(tpage(props, ["section", "requirements", "section", "surrounding-setup", "optional"]), {values:
	{
		bridge_name: resources.external.thomilist.project.division_result_bridge.name
	}})}
</p>

<ul>
	<li>
		{@html $t(tpage(props, ["section", "requirements", "section", "surrounding-setup", "opt0"]), {values:
		{
			meos_link: resources.external.melinsoftware.project.meos.route.website,
			meos_name: resources.external.melinsoftware.project.meos.name,
			meos_minimum_version: resources.external.melinsoftware.project.meos.version.infoserver
		}})}
	</li>
	<li>
		{@html $t(tpage(props, ["section", "requirements", "section", "surrounding-setup", "opt1"]), {values:
		{
			result_format: resources.external.iof.project.iof_xml_3.name
		}})}
	</li>
</ul>