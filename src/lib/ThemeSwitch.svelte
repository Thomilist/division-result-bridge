<script lang="ts">
    import { theme } from "$lib/stores";
    import { t } from "svelte-intl-precompile";
	import type { Theme, ThemeSwitchProps } from "./types";
	import PaletteFill from "svelte-bootstrap-icons/lib/PaletteFill.svelte";

    export let props: ThemeSwitchProps;

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



<label
    for="themeswitch"
    class="label-with-icon">

    <PaletteFill/>
    {$t(`${props.label}`)}:
</label>

<select
    bind:value="{$theme}"
    id="themeswitch">

    {#each themes as theme_name}
        <option value={theme_name}>
            {$t(`theme.${theme_name}.name`)}
        </option>
    {/each}
</select>
