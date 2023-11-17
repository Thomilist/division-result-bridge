<script lang="ts">
	import { theme, title } from "$lib/stores";
	import NavBar from "$lib/NavBar.svelte";
	import { browser } from "$app/environment";
	import Footer from "$lib/Footer.svelte";
	import type { LayoutData, Snapshot } from "./$types";
	import { afterNavigate } from "$app/navigation";
	import { onMount, tick } from "svelte";

	export let data: LayoutData;

	$: if (browser) document.documentElement.className = `themed ${$theme}`;

	// Scroll to top after navigating and (attempt to) keep scroll state when going back
	// https://github.com/sveltejs/kit/pull/8723#issuecomment-1423522635
	let container: HTMLElement;

    afterNavigate(() =>
    {
        container.scrollTo(0, 0);
    });

    export const snapshot: Snapshot<number> =
    {
        capture: () => container.scrollTop,
        restore: async (y) =>
		{
			await tick();
			container.scrollTo(0, y)
		}
    };

	onMount(() =>
	{
		const app_element: HTMLElement | null = document.querySelector("#app");
		
		if (app_element)
		{
			container = app_element;
		}
	});
</script>

<style lang="scss">
	@import "$styles/themes.scss";
	@import "$styles/fonts.scss";
	@import "$styles/base.scss";
	@import "$styles/hljs.scss";
</style>

<svelte:head>
    <title>
        {$title}
    </title>
</svelte:head>

<div id="app">
	<div class="sticky-nav">
		<NavBar props={data.nav}/>
	</div>

	<div class="scrollable-area">
		<main class="limited-width-container">
			<div class="limited-width-content">
				<slot/>
			</div>
		</main>

		<Footer/>
	</div>
</div>