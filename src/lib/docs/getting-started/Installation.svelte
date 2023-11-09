<script lang="ts">
	import type { DocPageProps } from "$lib/types";
	import DocHeader from "../DocHeader.svelte";

    export let props: DocPageProps;
</script>

<DocHeader props={{depth: 2, specifiers: ["section", "fresh-install", "title"], docpage: props}}/>

<DocHeader props={{depth: 2, specifiers: ["section", "update", "title"], docpage: props}}/>
