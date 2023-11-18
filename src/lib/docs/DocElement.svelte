<script lang="ts">
	import { t } from "svelte-intl-precompile";
	import { tpage } from "./docs";
	import type { DocElementProps } from "$lib/types";

    export let props: DocElementProps;
</script>

<svelte:element this={props.element ? props.element : "p"}>
	{@html $t(tpage(props.docpage, props.specifiers), {values: props.values})}
</svelte:element>