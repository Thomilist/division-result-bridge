<script lang="ts">
    import { theme } from "$lib/stores";
    import { t } from "svelte-intl-precompile";

    export let label: string = "";

    const themes: Theme[] =
    [
        "system",
        "light",
        "dark",
        "oled"
    ];
</script>

<label for="themeswitch">{label}</label>
<select bind:value="{$theme}" id="themeswitch">
    {#each themes as theme_name}
        <option value={theme_name}>{$t(`theme.${theme_name}.name`)}</option>
    {/each}
</select>