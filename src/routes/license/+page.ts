import type { PageLoad } from "./$types";

export const load: PageLoad = async ({ fetch }) =>
{
    const response = await fetch("https://raw.githubusercontent.com/Thomilist/division-result-bridge/main/LICENSE");

    if (!response.ok)
    {
        return {
            license: null
        };
    }

    const text = await response.text();
    const blocks = text.split("\n\n");

    const header = blocks[0];
    const project_meta_raw = blocks[1].split("\n");
    const license_meta_raw = blocks[2].split("\n");
    const license_text = blocks.slice(3);
    
    const project_meta =
    {
        name: project_meta_raw[0],
        version: project_meta_raw[1],
        link: project_meta_raw[2]
    };

    const intro_parts = license_meta_raw[0].split(/(<|>)/g);
    
    const license_meta =
    {
        intro:
        {
            start: intro_parts[0] + intro_parts[1],
            link: intro_parts[2],
            end: intro_parts[3]
        },
        identifier: license_meta_raw[1],
        copyright: license_meta_raw[2].replace("(c)", "©")
    };

    return {
        license:
        {
            header: header,
            project_meta: project_meta,
            license_meta: license_meta,
            text: license_text
        }
    };
}