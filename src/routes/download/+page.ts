import { isAssetsJson, isReleaseJson, type Release } from "$lib/types";
import { DateTime } from "luxon";
import type { PageLoad } from "./$types";
import { releases } from "$lib/stores";
import { get } from "svelte/store";

let cached = false;

export const load: PageLoad = async ({ fetch }) =>
{
    let success = true;
    
    release_fetch: if (!cached)
    {
        const response = await fetch("https://api.github.com/repos/Thomilist/division-result-bridge/releases");
        const releases_raw = await response.json();

        if (!releases_raw)
        {
            success = false;
            break release_fetch;
        }

        if (!Array.isArray(releases_raw))
        {
            success = false;
            break release_fetch;
        }

        releases_raw.forEach((rel) =>
        {
            if (!isReleaseJson(rel))
            {
                return;
            }

            let release: Release =
            {
                tag: rel.tag_name,
                draft: rel.draft,
                prerelease: rel.prerelease,
                link: rel.html_url,
                published_at: DateTime.fromISO(rel.published_at),
                text: rel.body,
                assets: []
            }

            rel.assets.forEach((asset) =>
            {
                if (!isAssetsJson(asset))
                {
                    return;
                }

                release.assets.push
                ({
                    name: asset.name,
                    download_link: asset.browser_download_url,
                    download_count: asset.download_count,
                    size: asset.size
                });
            });

            get(releases).push(release);
        });

        cached = true;
    }

    return {
        success: success
    };
}