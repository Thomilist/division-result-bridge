<script lang="ts">
	import { resources } from '$lib/resources';
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

<div class="home-page narrow-content">
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
                    {@html ($t(`page.home.highlights.${highlight}.content`, {values:
                    {
                        divi_name: resources.external.andersklinting.projects.divisionsmatchberegning.name,
                        divi_link: resources.external.andersklinting.projects.divisionsmatchberegning.routes.repo
                    }}))}
                </p>
            </div>
        {/each}
    </div>
</div>