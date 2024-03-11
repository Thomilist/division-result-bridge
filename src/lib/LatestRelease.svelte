<script lang="ts">
    import { t } from "svelte-intl-precompile";
    import Download from "svelte-bootstrap-icons/lib/Download.svelte";
	import type { Release, ReleaseMeta } from "./types";

    export let release: Release | undefined;
    export let meta: ReleaseMeta | undefined;
</script>



<style lang="scss">
    @import "$styles/latest-release.scss";
</style>



{#if release && meta && meta.assets[0]}
    <div class="latest-release">
        <h1>
            {$t("page.download.latest.header")}
        </h1>
        
        <a
            href="{release.assets[0].download_link}"
            class="download-latest-button">

            <Download width=1em height=1em/>
            {$t("page.download.latest.button")}
        </a>

        <div class="download-latest-details">
            <div>
                {
                    @html
                    $t("page.download.latest.details.version", { values:
                    {
                        version: meta.version.full,
                        platform: meta.assets[0].platform,
                        arch: meta.assets[0].arch
                    }})
                }
            </div>

            <div>
                {
                    @html
                    $t("page.download.latest.details.file", { values:
                    {
                        format: meta.assets[0].format,
                        size: meta.assets[0].size.pretty
                    }})
                }
            </div>
        </div>
    </div>
{/if}
