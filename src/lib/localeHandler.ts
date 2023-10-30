import { getLocaleFromNavigator } from "svelte-intl-precompile";

export const default_locale = "en";

const locale_names =
{
    "system": "language.system.name",
    "da": "language.da.name",
    "en": "language.en.name"
};

const locale_map = new Map(Object.entries(locale_names));

export function localeName(identifier: string): string
{
    const name = locale_map.get(identifier);

    if (!name)
    {
        return "language.undefined.name";
    }

    return name;
}

export function localeFromStore(identifier: string): string
{
    if (identifier === "system")
    {
        const browser_locale = getLocaleFromNavigator();

        if (!browser_locale)
        {
            return default_locale;
        }

        return browser_locale.substring(0, 2);
    }
    else if (locale_map.has(identifier))
    {
        return identifier;
    }
    else
    {
        return default_locale;
    }
}