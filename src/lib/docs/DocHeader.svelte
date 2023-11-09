<script lang="ts">
	import type { DocHeaderProps } from "$lib/types";
	import { t } from "svelte-intl-precompile";
	import { tcol, tpage } from "./docs";
	import { title } from "$lib/stores";

    export let props: DocHeaderProps;

    const is_main = (props.depth === 0);

    if (is_main)
    {
        $title = `${$t(tpage(props.docpage, props.specifiers))} - ${$t("project.name")}`;
    }
</script>

<style lang="scss">
    @import "$styles/doc-header.scss";
</style>

{#if is_main}
    <span class="doc-collection-label">
        {$t(tcol(props.docpage, ["title"]))}
    </span>    
{/if}

<svelte:element this={`h${is_main ? 1 : props.depth}`} class="doc-header {is_main ? "doc-header-main": ""}" id="{props.specifiers.join("_")}">
    {$t(tpage(props.docpage, props.specifiers))}
</svelte:element>