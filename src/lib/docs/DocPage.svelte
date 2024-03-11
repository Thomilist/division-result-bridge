<script lang="ts">
	import type { DocPage } from "$lib/types";
	import DocHeader from "./DocHeader.svelte";

    export let props: DocPage;
</script>



<DocHeader props=
{{
	depth: 0,
	specifiers: ["title"],
	docpage: props.props
}}/>

<svelte:component this={props.component} props={props.props}/>
