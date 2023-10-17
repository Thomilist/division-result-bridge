<script lang="ts">
    import { t, locale, locales } from "svelte-intl-precompile";
	import { locale_map } from "./locale-names";
</script>

<select bind:value="{$locale}">
    {#each $locales as loc}
        <option value={loc}>{locale_map.get(loc)}</option>
    {/each}
</select>