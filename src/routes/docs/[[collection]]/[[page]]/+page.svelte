<script lang="ts">
	import { doc_path } from "$lib/stores";
	import type { PageData } from "./$types";
	import DocHeader from "$lib/docs/DocHeader.svelte";
	import { t } from "svelte-intl-precompile";
	import { tpage } from "$lib/docs/docs";
	import DocPage from "$lib/docs/DocPage.svelte";

	export let data: PageData;

    $: collection = data.docs.get(`${data.params.collection}`);
    $: page = collection?.pages.get(`${data.params.page}`);

    $: [collection, page], $doc_path =
    {
        collection: page ? `${collection?.title}` : "undefined",
        page: `${page?.props.title}`
    };

    $: header_props =
    {
        collection: $doc_path.collection,
        title: $doc_path.page
    };
</script>

{#if page}
    <DocPage props={page}/>
{:else}
    <DocHeader props={{depth: 0, specifiers: ["title"], docpage: header_props}}/>

    <p>
        {$t(tpage(header_props, ["message"]))}
    </p>
{/if}