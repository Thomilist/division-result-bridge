<script lang="ts">
	import { theme } from "$lib/stores";
	import NavBar from "$lib/NavBar.svelte";
	import { browser } from "$app/environment";
	import Footer from "$lib/Footer.svelte";

	$: if (browser) document.documentElement.className = `themed ${$theme}`;
</script>

<style lang="scss">
	@import "$styles/themes.scss";
	@import "$styles/fonts.scss";
	@import "$styles/base.scss";
	@import "$styles/hljs.scss";
</style>

<div id="app">
	<div class="sticky-nav">
		<NavBar/>
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