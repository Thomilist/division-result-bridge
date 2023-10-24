<script lang="ts">
	import { theme } from "$lib/stores";
	import Navbar from "$lib/Navbar.svelte";
	import { browser } from "$app/environment";

	$: if (browser) document.documentElement.className = `themed ${$theme}`;
</script>

<style lang="scss">
	@import "$styles/themes.scss";
	@import "$styles/fonts.scss";
	@import "$styles/base.scss";
</style>

<Navbar/>

<main class="limited-width-container">
	<div class="limited-width-content">
		<slot/>
	</div>
</main>