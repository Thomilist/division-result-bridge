import byteSize from "byte-size";
import type { AssetMeta, Release, ReleaseMeta } from "./types";

const platform_names =
{
    "windows": "Windows",
    "linux": "Linux",
    "macos": "macOS"
};

const platform_name_map = new Map(Object.entries(platform_names));

export function releaseMeta(release: Release): ReleaseMeta
{
    const version_digits = release.tag.split(".");
    const assets: AssetMeta[] = [];

    release.assets.forEach((asset) =>
    {
        const file_extention_index = asset.name.lastIndexOf(".");
        const file_extention = asset.name.substring(file_extention_index + 1).toUpperCase();
        const file_name = asset.name.substring(0, file_extention_index);

        const name_parts = file_name.split("-");
        const platform_raw = name_parts.at(-2);

        if (!platform_raw)
        {
            return;
        }

        const platform = platform_name_map.get(platform_raw);

        if (!platform)
        {
            return;
        }

        const arch = name_parts.at(-1);

        if (!arch)
        {
            return;
        }

        assets.push
        ({
            platform: platform,
            arch: arch,
            format: file_extention,
            size:
            {
                bytes: asset.size,
                pretty: byteSize(asset.size, {units: "iec"}).toString()
            }
        });
    });

    return {
        version:
        {
            full: release.tag,
            major: parseInt(version_digits[0]),
            minor: parseInt(version_digits[1]),
            patch: parseInt(version_digits[2])
        },
        assets: assets
    };
}
