<script lang="ts">
	import DocFooter from "$lib/docs/DocFooter.svelte";
    import DocNav from "$lib/docs/DocNav.svelte";
	import DocPageNav from "$lib/docs/DocPageNav.svelte";
	import { doc_path } from "$lib/stores";
    import type { LayoutData } from "./$types";

    export let data: LayoutData;
</script>

<style lang="scss">
    @import "$styles/docs.scss";
    @import "$styles/doc-header.scss";
</style>

<div class="docs">
    <div class="doc-nav-container">
        <DocNav collections={Array.from(data.docs.values())}/>
    </div>
    
    <div class="doc-content-container">
        <slot/>
    </div>

    <div class="doc-footer-container">
        <DocFooter props={{collection: data.docs.get($doc_path.collection)}}/>
    </div>
    
    <div class="doc-page-nav-container">
        <DocPageNav />
    </div>
</div>