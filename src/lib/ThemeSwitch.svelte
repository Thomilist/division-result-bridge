<script lang="ts">
    import { theme } from "$lib/stores";
    import { t } from "svelte-intl-precompile";

    const themes: Theme[] =
    [
        "system",
        "light",
        "dark",
        "oled"
    ];
</script>

<select bind:value="{$theme}">
    {#each themes as theme_name}
        <option value={theme_name}>{$t(`theme.${theme_name}.name`)}</option>
    {/each}
</select>