<script lang="ts">
    import { t, locale, locales } from "svelte-intl-precompile";
	import { localeFromStore, localeName } from "./localeHandler";
    import Translate from "svelte-bootstrap-icons/lib/Translate.svelte";
	import { language } from "./stores";
	import type { LanguageSelectProps } from "./types";

    export let props: LanguageSelectProps;

    const values = ["system", ...$locales];
    
    $: { $locale = localeFromStore($language); }
</script>



<style lang="scss">
    @import "$styles/label-with-icon.scss";
</style>



<label for="languageselect" class="label-with-icon"><Translate/>
    {$t(`${props.label}`)}:
</label>

<select bind:value="{$language}" id="languageselect">
    {#each values as lang}
        <option value={lang}>
            {$t(localeName(lang))}
        </option>
    {/each}
</select>
