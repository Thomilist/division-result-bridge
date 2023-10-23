<script lang="ts">
    import { theme } from "$lib/stores";
    import { t } from "svelte-intl-precompile";
	import ThemeIcon from "./icons/ThemeIcon.svelte";

    export let label: string = "";

    const themes: Theme[] =
    [
        "system",
        "light",
        "dark",
        "oled"
    ];
</script>

<style lang="scss">
    @import "$styles/label-with-icon.scss";
</style>

<label for="themeswitch" class="label-with-icon"><ThemeIcon/>{$t(`${label}`)}:</label>
<select bind:value="{$theme}" id="themeswitch">
    {#each themes as theme_name}
        <option value={theme_name}>{$t(`theme.${theme_name}.name`)}</option>
    {/each}
</select>