<script lang="ts">
	import NavLink from "$lib/NavLink.svelte";
	import { doc_path } from "$lib/stores";
	import type { DocFooterProps, DocPageProps } from "$lib/types";
	import { t } from "svelte-intl-precompile";
	import { tpage } from "./docs";

	export let props: DocFooterProps;

	let previous: DocPageProps;
	let next: DocPageProps;

	$: if (props.collection?.pages.has($doc_path.page))
	{
		const page_names = Array.from(props.collection.pages.keys());
		const current_index = page_names.indexOf($doc_path.page);

		previous =
		{
			title: page_names[current_index - 1],
			collection: props.collection.title
		};
		next =
		{
			title: page_names[current_index + 1],
			collection: props.collection.title
		};
	}
</script>



<style lang="scss">
	@import "$styles/doc-footer.scss";
</style>



{#if props.collection?.connected && (previous?.title || next?.title)}
	<div class="doc-footer">
		{#if previous.title}
			<div class="doc-footer-previous">
				<span class="doc-footer-label">
					{$t("page.docs.nav.previous")}
				</span>

				<NavLink props=
				{{
					label: tpage(previous, ["title"]),
					route: `/docs/${previous.collection}/${previous.title}`
				}}/>
			</div>
		{/if}

		{#if next.title}
			<div class="doc-footer-next">
				<span class="doc-footer-label">
					{$t("page.docs.nav.next")}
				</span>

				<NavLink props=
				{{
					label: tpage(next, ["title"]),
					route: `/docs/${next.collection}/${next.title}`
				}}/>
			</div>
		{/if}
	</div>
{/if}
