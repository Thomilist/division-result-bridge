<script lang="ts">
    import { locale, t } from "svelte-intl-precompile";
	import type { Release, ReleaseMeta } from "./types";
	import { htmlFromMarkdown } from "./htmlFromMarkdown";
	import { DateTime } from "luxon";

    export let release: Release;
    export let meta: ReleaseMeta;
</script>



<style lang="scss">
    @import "$styles/release.scss";
</style>



<div class="release">
    <div class="release-header">
        <h2 class="release-name">
            {$t("project.name")} {meta.version.full}
        </h2>

        {#if release.prerelease}
            <span class="release-pre">
                {$t("page.download.releases.prerelease")}
            </span>
        {/if}
    
        <span class="release-date">
            {release.published_at.setLocale($locale).toLocaleString({...DateTime.DATETIME_FULL, timeZoneName: undefined})}
        </span>
    </div>

    <div class="release-files">
        {#if release.assets.length > 0}
            <table>
                <tr class="release-files-header">
                    <th>
                        {$t("page.download.releases.files.labels.name")}
                    </th>
                    <th>
                        {$t("page.download.releases.files.labels.platform")}
                    </th>
                    <th>
                        {$t("page.download.releases.files.labels.arch")}
                    </th>
                    <th>
                        {$t("page.download.releases.files.labels.format")}
                    </th>
                    <th>
                        {$t("page.download.releases.files.labels.size")}
                    </th>
                </tr>

                {#each meta.assets as metadata, index}
                    <tr class="release-files-row">
                        <td>
                            <a href="{release.assets[index].download_link}">
                                {release.assets[index].name}
                            </a>
                        </td>
                        <td>
                            {metadata.platform}
                        </td>
                        <td>
                            {metadata.arch}
                        </td>
                        <td>
                            {metadata.format}
                        </td>
                        <td>
                            {metadata.size.pretty}
                        </td>
                    </tr>
                {/each}
            </table>
        {:else}
            <p class="release-files-empty">
                {$t("page.download.releases.empty")}
            </p>
        {/if}
    </div>

    <details class="release-notes">
        <summary>
            {$t("page.download.releases.notes")}
        </summary>

        <div class="release-note-content">
            {#await htmlFromMarkdown(release.text)}
                {$t("page.download.releases.loading")}
            {:then notes}
                {@html notes}
            {/await}
        </div>
    </details>

    <a
        href={release.link}
        target="_blank"
        class="release-link">
        
        {$t("page.download.releases.github")}
    </a>
</div>
