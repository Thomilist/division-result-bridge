<script lang="ts">
    import { t } from 'svelte-intl-precompile';

    const highlights =
    [
        "compatibility",
        "setup",
        "foss"
    ];
</script>

<style lang="scss">
    @import "$styles/home.scss";
</style>

<svelte:head>
    <title>
        {$t("page.home.title")}
    </title>
</svelte:head>

<div class="home-page">
    <div class="cover">
        <h1>
            {$t("page.home.title")}
        </h1>
        
        <p>
            {$t("page.home.subtitle")}
        </p>
    </div>
    
    <div class="highlights">
        {#each highlights as highlight}
            <div class="highlight">
                <h2>
                    {$t(`page.home.highlights.${highlight}.title`)}
                </h2>
    
                <p>
                    {@html ($t(`page.home.highlights.${highlight}.content`))}
                </p>
            </div>
        {/each}
    </div>
</div>