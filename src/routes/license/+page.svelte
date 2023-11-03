<script lang="ts">
    import { t } from "svelte-intl-precompile";
    import type { PageData } from "./$types";
    
    export let data: PageData;
    const license = data.license;
</script>

<style lang="scss">
    @import "$styles/license.scss";
</style>

<svelte:head>
    <title>
        {$t("page.license.title")} - {$t("project.name")}
    </title>
</svelte:head>

<div class="narrow-content">
    {#if license}
        <h1>
            {license.header}
        </h1>

        <div class="license-items">
            <ul>
                <li>
                    {license.project_meta.name}
                </li>
                <li>
                    {license.project_meta.version}
                </li>
                <li>
                    <a href="{license.project_meta.link}" target="_blank">
                        {license.project_meta.link}
                    </a>
                </li>
            </ul>
        
            <ul>
                <li>
                    {license.license_meta.intro.text}
                    
                    <span class="no-break">
                        {license.license_meta.intro.open}
                        <a href="{license.license_meta.intro.link}" target="_blank">
                            {license.license_meta.intro.link}
                        </a>
                        {license.license_meta.intro.close}
                    </span>
                </li>
                <li>
                    {license.license_meta.identifier}
                </li>
                <li>
                    {license.license_meta.copyright}
                </li>
            </ul>
        
            {#each license.text as text}
                <div>
                    {text}
                </div>
            {/each}
        </div>
    {:else}
        <h1>
            {$t("page.license.title")}
        </h1>

        <p>
            {$t("page.license.fallback")}
        </p>
    {/if}
</div>