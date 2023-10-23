<script lang="ts">
    import { t, locale, locales } from "svelte-intl-precompile";
	import { locale_map } from "./locale-names";
	import TranslateIcon from "./icons/TranslateIcon.svelte";

    export let label: string = "";
</script>

<style lang="scss">
    @import "$styles/label-with-icon.scss";
</style>

<label for="languageselect" class="label-with-icon"><TranslateIcon/>{$t(`${label}`)}:</label>
<select bind:value="{$locale}" id="languageselect">
    {#each $locales as loc}
        <option value={loc}>{locale_map.get(loc)}</option>
    {/each}
</select>