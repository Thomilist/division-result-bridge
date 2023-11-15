<script lang="ts">
    import { releases, title } from "$lib/stores";
    import { t } from "svelte-intl-precompile";
	import { releaseMeta } from "$lib/releaseMeta";
	import LatestRelease from "$lib/LatestRelease.svelte";
	import Release from "$lib/Release.svelte";
	import { resources } from "$lib/resources";

    const has_releases = $releases.some(rel => !rel.draft);
    const latest_release = $releases.find(rel => !rel.draft && !rel.prerelease);
    const latest_release_meta = latest_release ? releaseMeta(latest_release) : undefined;
    const all_releases = $releases.filter(rel => !rel.draft);
    const all_releases_meta = all_releases.map(rel => releaseMeta(rel));

    $title = `${$t("page.download.title")} - ${$t("project.name")}`;
</script>

<style lang="scss">
    @import "$styles/download.scss";
</style>

<div class="narrow-content">
    {#if has_releases}
        <div class="releases">
            <LatestRelease release={latest_release} meta={latest_release_meta}/>

            <div class="all-releases">
                <h1>
                    {$t("page.download.releases.title")}
                </h1>

                {#each all_releases as release, index}
                    <Release release={release} meta={all_releases_meta[index]}/>
                {/each}
            </div>
        </div>
    {:else}
        <h1>
            {$t("page.download.empty.title")}
        </h1>

        <p>
            {@html $t("page.download.empty.message", {values: {releases_link: resources.external.thomilist.project.division_result_bridge.route.releases}})}
        </p>
    {/if}
</div>