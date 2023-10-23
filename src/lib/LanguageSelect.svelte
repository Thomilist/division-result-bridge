<script lang="ts">
    import { t, locale, locales } from "svelte-intl-precompile";
	import { locale_map } from "./locale-names";

    export let label: string = "";
</script>

<label for="languageselect">{$t(`${label}`)}:</label>
<select bind:value="{$locale}" id="languageselect">
    {#each $locales as loc}
        <option value={loc}>{locale_map.get(loc)}</option>
    {/each}
</select>