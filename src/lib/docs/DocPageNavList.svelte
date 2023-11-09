<script lang="ts">
	import NavLink from "$lib/NavLink.svelte";
    import type { DocPageNavListProps } from "$lib/types";

    export let props: DocPageNavListProps;
</script>

<style lang="scss">
    @import "$styles/doc-page-nav-list.scss";
</style>

<ol>
    {#each props.headers as header}
        <li>
            {#if (header.node instanceof Element && header.node.id.length > 0)}
                <NavLink props={{label: `${header.node.textContent}`, skip_translation: true, route: `#${header.node.id}`}}/>
            {:else}
                {header.node.textContent}
            {/if}
        </li>

        <svelte:self props={{headers: header.children}}/>
    {/each}
</ol>