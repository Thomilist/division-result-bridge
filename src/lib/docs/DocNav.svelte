<script lang="ts">
	import NavLink from "$lib/NavLink.svelte";
	import { docpath } from "$lib/stores";
    import type { DocCollection } from "$lib/types";
	import { t } from "svelte-intl-precompile";

    export let collections: DocCollection[];
</script>

<style lang="scss">
    @import "$styles/doc-nav.scss";
</style>

<div class="doc-nav">
    <nav>
        {#each collections as collection}
            <div class="doc-nav-collection">
                <h2 class="doc-collection-label">
                    {$t(`page.docs.collection.${collection.title}.title`)}
                </h2>
        
                <svelte:element this={collection.connected ? "ol" : "ul"}>
                    {#each collection.pages as page}
                        <li class="{(collection.title === $docpath.collection && page[0] === $docpath.page) ? "active-docpage": ""}">
                            <NavLink props={{
                                label: `page.docs.collection.${collection.title}.page.${page[0]}.title`,
                                route: `/docs/${collection.title}/${page[0]}`}}
                            />
                        </li>
                    {/each}
                </svelte:element>
            </div>
        {/each}
    </nav>
</div>